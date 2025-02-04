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

#ifndef _LOGIN_DIALOG_H_
#define _LOGIN_DIALOG_H_

#include "../libkvnc_client_config/ViewerConfig.h"
#include "../libkvnc_client_config/ConnectionConfig.h"
#include "../libkvnc_client_config/ConnectionConfigSM.h"
#include "../libkvnc_client_config/ViewerSettingsManager.h"
#include "../libkvnc_all_util/StringParser.h"
#include "../libkvnc_all_gui/BaseDialog.h"
#include "../libkvnc_all_gui/TextBox.h"
#include "../libkvnc_all_gui/CheckBox.h"
#include "../libkvnc_all_gui/ComboBox.h"
#include "../libkvnc_all_gui/TrackBar.h"

#include "TvnViewer.h"
#include "kvnc_client_Resource.h"

class TvnViewer;

class LoginDialog : public BaseDialog
{
public:
  LoginDialog(TvnViewer *viewer);
  ~LoginDialog();

  // this function returns the host
  StringStorage getServerHost();
  void setConConf(ConnectionConfig *conConf);
  // set listening mode
  void setListening(bool isListening);

  static const int DEFAULT_PORT = 5959;

  // this constant will be returned if user have pressed 'Connect...' button
  static const int CANCEL_MODE = 0;
  // this constant will be returned if user have pressed 'Cancel' button
  static const int CONNECTION_MODE = 1;
  // this constant will be returned if user have pressed 'Listening' button
  static const int LISTENING_MODE = 2;

protected:
  BOOL onInitDialog();
  BOOL onCommand(UINT controlID, UINT notificationID);
  bool m_isListening;

  Control m_listening;
  Control m_ok;
  ConnectionConfig m_connectionConfig;
  ComboBox m_server;
  StringStorage m_serverHost;
  TvnViewer *m_viewer;

private:
  void enableConnect();
  void updateHistory();
  void onConnect();
  void onConfiguration();
  BOOL onOptions();
  void onOrder();
  void openUrl(const TCHAR *url);
  void onListening();
  void onAbout();
};

#endif
