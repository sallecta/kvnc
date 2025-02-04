// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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

#include "LocalWindowsApplication.h"

#include "../libkvnc_all_util/winhdr.h"
#include "../libkvnc_all_thread/DesktopSelector.h"

LocalWindowsApplication::LocalWindowsApplication(HINSTANCE hInstance,
                                                 const TCHAR *windowClassName)
 : WindowsApplication(hInstance, windowClassName)
{
  HWINSTA winSta = 0;

  winSta = OpenWindowStation(_T("WinSta0"), TRUE, GENERIC_ALL);

  if (winSta== 0) {
    throw SystemException();
  }

  if (SetProcessWindowStation(winSta) == 0) {
    CloseWindowStation(winSta);
    throw SystemException();
  }

  CloseWindowStation(winSta);

  // FIXME: why we don't check returning values?
  DesktopSelector::selectDesktop();
}

LocalWindowsApplication::~LocalWindowsApplication()
{
}
