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

#ifndef _FS_WARNING_DIALOG_H_
#define _FS_WARNING_DIALOG_H_

#include "../libkvnc_all_gui/BaseDialog.h"
#include "../libkvnc_all_gui/CheckBox.h"
#include "kvnc_client_Resource.h"

class FsWarningDialog : public BaseDialog
{
public:
  FsWarningDialog();
  bool isFsWarning();

protected:
  BOOL onInitDialog();
  BOOL onCommand(UINT controlID, UINT notificationID);

  CheckBox m_fsWarning;
};

#endif
