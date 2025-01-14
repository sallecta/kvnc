// Copyright (C) 2011,2012 GlavSoft LLC.
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

#ifndef _COPY_RECT_DECODER_H_
#define _COPY_RECT_DECODER_H_

#include "DecoderOfRectangle.h"

#include "../libkvnc_all_region/Point.h"

class CopyRectDecoder : public DecoderOfRectangle
{
public:
  CopyRectDecoder(LogWriter *logWriter);
  virtual ~CopyRectDecoder();

protected:
  //
  // This method inherited by DecoderOfRectangle.
  //
  virtual void decode(RfbInputGate *input,
                      lkvnc_rfb_FrameBuffer *lkvnc_rfb_FrameBuffer,
                      const Rect *dstRect);

  //
  // This method inherited by DecoderOfRectangle.
  //
  virtual void copy(lkvnc_rfb_FrameBuffer *dstFrameBuffer,
                    const lkvnc_rfb_FrameBuffer *srcFrameBuffer,
                    const Rect *rect,
                    LocalMutex *fbLock);

private:
  // This Point save left-top corner of copy-rectangle.
  Point m_sourcePosition;
};

#endif
