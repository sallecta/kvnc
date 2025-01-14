// Copyright (C) 2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#include "CursorUpdates.h"
#include "../libkvnc_all_thread/AutoLock.h"

CursorUpdates::CursorUpdates(LogWriter *log)
: m_blockCurPosTime(0),
  m_isDrawCursorMethod(false),
  m_log(log)
{
}

CursorUpdates::~CursorUpdates()
{
}

void CursorUpdates::update(const EncodeOptions *encodeOptions,
                           UpdateContainer *updCont,
                           bool fullRegReq,
                           const Rect *viewPort,
                           bool shareOnlyApp,
                           const Region *shareAppRegion,
                           lkvnc_rfb_FrameBuffer *fb,
                           lkvnc_rfb_CursorShape *lkvnc_rfb_CursorShape)
{
  // Check cursor events. If they are outside of shared region then ignore they.
  if (shareOnlyApp) {
    bool inside = shareAppRegion->isPointInside(updCont->cursorPos.x, updCont->cursorPos.y);
    if (!inside) {
      updCont->cursorPosChanged = false;
      updCont->lkvnc_rfb_CursorShapeChanged = false;
    }
  }

  bool richEnabled = encodeOptions->richCursorEnabled();
  bool posEnabled = encodeOptions->pointerPosEnabled();

  bool posChanged = updCont->cursorPosChanged;
  // The posChanged and updCont->cursorPosChanged flags has different
  // purpose. The posChanged will be always raised if position real changed
  // but the updCont->cursorPosChanged flag can be raised only cursor pos
  // is not blocked.
  if (posChanged) {
    m_log->debug(_T("Checking cursor position"));
    bool cursorPosBlockingIsIgnored = !richEnabled;
    posChanged = checkCursorPos(updCont, viewPort, cursorPosBlockingIsIgnored);
  }

  if (!richEnabled && !posEnabled) {
    // Draw the shape on the frame buffer.
    drawCursor(updCont, fb);
  }

  bool initShapeByZeroIsNeeded = false;
  if (richEnabled && !posEnabled) {
    bool methodWasChanged = false;
    if (updCont->cursorPosChanged) { // The move by the server
      methodWasChanged = !m_isDrawCursorMethod;
      if (methodWasChanged) {
        m_isDrawCursorMethod = true;
        // By cursor shape method will be sended zero shape.
        initShapeByZeroIsNeeded = true;
      }
    } else if (posChanged) { // The move by the client.
      methodWasChanged = m_isDrawCursorMethod;
      if (methodWasChanged) {
        m_isDrawCursorMethod = false;
        // Restore background under the cursor shape
        restoreFrameBuffer(fb);
        Rect backgroundRect = getBackgroundRect();
        updCont->changedRegion.addRect(&backgroundRect);
      }
    }
    if (m_isDrawCursorMethod) {
      drawCursor(updCont, fb);
      updCont->lkvnc_rfb_CursorShapeChanged = methodWasChanged;
    } else {
      updCont->lkvnc_rfb_CursorShapeChanged = updCont->lkvnc_rfb_CursorShapeChanged ||
                                    methodWasChanged;
    }
  }

  if (!richEnabled || !posEnabled) {
    m_log->debug(_T("Clearing cursorPosChanged")
               _T(" (RichCursor or PointerPos are not requested)"));
    updCont->cursorPosChanged = false;
  } else if (fullRegReq) {
    m_log->debug(_T("Raising cursorPosChanged (full region requested)"));
    updCont->cursorPosChanged = true;
  }
  if (!richEnabled) {
    m_log->debug(_T("Clearing lkvnc_rfb_CursorShapeChanged (RichCursor disabled)"));
    updCont->lkvnc_rfb_CursorShapeChanged = false;
  } else if (fullRegReq) {
    m_log->debug(_T("Raising lkvnc_rfb_CursorShapeChanged (RichCursor enabled")
               _T(" and full region requested)"));
    updCont->lkvnc_rfb_CursorShapeChanged = true;
  }
  if (updCont->lkvnc_rfb_CursorShapeChanged) {
    extractCursorShape(lkvnc_rfb_CursorShape);
    if (initShapeByZeroIsNeeded) {
      lkvnc_rfb_CursorShape->resetToEmpty();
    }
  }
}

void CursorUpdates::restoreFrameBuffer(lkvnc_rfb_FrameBuffer *fb)
{
  AutoLock al(&m_curPosLocMut);
  Rect dstRect = m_shapeBackground.getDimension().getRect();
  dstRect.setLocation(m_backgroundPos.x, m_backgroundPos.y);
  fb->copyFrom(&dstRect, &m_shapeBackground, 0, 0);
  // m_shapeBackground.setDimension(&Dimension(0, 0));
}

void CursorUpdates::drawCursor(UpdateContainer *updCont, lkvnc_rfb_FrameBuffer *fb)
{
  AutoLock al(&m_curPosLocMut);
  // Add previous background rectangle to the changed region.
  Rect tmpRect = m_shapeBackground.getDimension().getRect();
  Rect rect(&tmpRect);
  rect.setLocation(m_backgroundPos.x, m_backgroundPos.y);
  updCont->changedRegion.addRect(&rect);
  // Keep the current background rectangle.
  Point hotSpot = m_cursorShape.getHotSpot();
  m_backgroundPos.setPoint(m_cursorPos.x - hotSpot.x,
                           m_cursorPos.y - hotSpot.y);
  Dimension tmpDimension =m_cursorShape.getDimension();
  lkvnc_rfb_PixelFormat tmpPixelFormat =m_cursorShape.getPixelFormat();
  m_shapeBackground.setProperties(&tmpDimension, &tmpPixelFormat);
  // Keep background under cursor shape to can reconstruct full image.
  m_shapeBackground.copyFrom(fb,
                             m_backgroundPos.x,
                             m_backgroundPos.y);
  // Draw the cursor shape on the frame buffer
  tmpRect = m_cursorShape.getDimension().getRect();
  rect.setRect(&tmpRect);
  rect.setLocation(m_backgroundPos.x, m_backgroundPos.y);

  fb->overlay(&rect,
              m_cursorShape.getPixels(), 0, 0,
              m_cursorShape.getMask());
}

bool CursorUpdates::checkCursorPos(UpdateContainer *updCont,
                                   const Rect *viewPort,
                                   bool curPosBlockingIsIgnored)
{
  AutoLock al(&m_curPosLocMut);
  Point cursorPos = updCont->cursorPos;
  cursorPos.x -= viewPort->left;
  cursorPos.y -= viewPort->top;

  if (cursorPos.x < 0) {
    cursorPos.x = 0;
  } else if (cursorPos.x >= viewPort->getWidth()) {
    cursorPos.x = viewPort->getWidth() - 1;
  }
  if (cursorPos.y < 0) {
    cursorPos.y = 0;
  } else if (cursorPos.y >= viewPort->getHeight()) {
    cursorPos.y = viewPort->getHeight() - 1;
  }

  bool isBlocked = isCursorPosBlocked() && !curPosBlockingIsIgnored;
  bool positionChanged = cursorPos.x != m_cursorPos.x ||
                         cursorPos.y != m_cursorPos.y;
  if (!positionChanged || isBlocked) {
    updCont->cursorPosChanged = false;
  } else {
    m_cursorPos.x = cursorPos.x;
    m_cursorPos.y = cursorPos.y;
  }
  return positionChanged;
}

void CursorUpdates::blockCursorPosSending()
{
  AutoLock al(&m_curPosLocMut);
  // Block cursor pos sending to a time interval.
  m_blockCurPosTime = DateTime::now();
}

bool CursorUpdates::isCursorPosBlocked()
{
  AutoLock al(&m_curPosLocMut);
  if ((DateTime::now() - m_blockCurPosTime).getTime() > 1000) {
    return false; // Unblocked
  } else {
    return true; // Blocked
  }
}

Point CursorUpdates::getCurPos()
{
  AutoLock al(&m_curPosLocMut);
  return m_cursorPos;
}

Rect CursorUpdates::getBackgroundRect()
{
  AutoLock al(&m_curPosLocMut);
  Rect tmpRect = m_shapeBackground.getDimension().getRect();
  Rect rect(&tmpRect);
  rect.setLocation(m_backgroundPos.x, m_backgroundPos.y);
  return rect;
}

void CursorUpdates::updateCursorShape(const lkvnc_rfb_CursorShape *curShape)
{
  AutoLock al(&m_curPosLocMut);
  m_cursorShape.clone(curShape);
}

void CursorUpdates::extractCursorShape(lkvnc_rfb_CursorShape *curShape)
{
  AutoLock al(&m_curPosLocMut);
  curShape->clone(&m_cursorShape);
}
