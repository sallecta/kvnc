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

#ifndef _CONFIGURATION_DIALOG_H_
#define _CONFIGURATION_DIALOG_H_

#include "../libkvnc_client_config/ViewerConfig.h"
#include "../libkvnc_client_config/ConnectionConfig.h"
#include "../libkvnc_client_config/ConnectionConfigSM.h"
#include "../libkvnc_client_config/ViewerSettingsManager.h"
#include "../libkvnc_all_util/StringParser.h"
#include "../libkvnc_all_gui/BaseDialog.h"
#include "../libkvnc_all_gui/Control.h"
#include "../libkvnc_all_gui/TextBox.h"
#include "../libkvnc_all_gui/CheckBox.h"
#include "../libkvnc_all_gui/SpinControl.h"
#include "../libkvnc_all_gui/ComboBox.h"
#include "../libkvnc_all_gui/TrackBar.h"
#include "kvnc_client_Resource.h"

#include "../libkvnc_all_winSystem/WindowsApplication.h"

class ConfigurationDialog : public BaseDialog
{
public:
  ConfigurationDialog();

  void setListenerOfUpdate(WindowsApplication *application);

protected:
  BOOL onCommand(UINT controlID, UINT notificationID);
  void onLogLevelChange();
  void onOpenFolderButtonClick();
  BOOL onInitDialog();

  CheckBox m_showToolBars;
  CheckBox m_warnAtSwitching;
  CheckBox m_autoRec;
  CheckBox m_askComment;
  TextBox m_vidPath;
  TextBox m_peerName;
  TextBox m_numberConn;
  SpinControl m_snumConn;
  TextBox m_reverseConn;
  SpinControl m_sreverseConn;
  TextBox m_verbLvl;
  SpinControl m_sverbLvl;
  TextBox m_logging;
  Control m_openLogDir;

  WindowsApplication *m_application;

private:
  void updateControlValues();
  bool isInputValid();
  bool testNum(TextBox *tb, const TCHAR *tbName);
  void onOkPressed();
};

#endif
