// Copyright (C) 2012 GlavSoft LLC.
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

#ifndef _PAINT_WINDOW_H_
#define _PAINT_WINDOW_H_

#include "BaseWindow.h"
#include "drawing/DeviceContext.h"

class PaintWindow: public BaseWindow
{
public:
  PaintWindow();
  virtual ~PaintWindow();
  HDC getHDCPaint();

private:

  friend class DeviceContext;

protected:
  virtual void onPaint(DeviceContext *dc, PAINTSTRUCT *paintStruct);

  bool wndProc(UINT message, WPARAM wParam, LPARAM lParam);

  bool m_bIsDraw;
  PAINTSTRUCT m_paintStruct;
  HDC m_hdc;

};

#endif
