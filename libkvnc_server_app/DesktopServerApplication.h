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

#ifndef __DESKTOP_SERVER_APPLICATION_H__
#define __DESKTOP_SERVER_APPLICATION_H__

#include "../libkvnc_all_winSystem/WindowsApplication.h"
#include "../libkvnc_all_util/AnEventListener.h"
#include "../libkvnc_all_winSystem/AnonymousPipe.h"
#include "../libkvnc_server_desktopIpc/BlockingGate.h"
#include "../libkvnc_server_desktopIpc/DesktopSrvDispatcher.h"
#include "../libkvnc_server_desktopIpc/UpdateHandlerServer.h"
#include "../libkvnc_server_desktopIpc/UserInputServer.h"
#include "../libkvnc_server_desktopIpc/ConfigServer.h"
#include "../libkvnc_server_desktopIpc/GateKickHandler.h"
#include "SessionChangesWatcher.h"
#include "../libkvnc_all_winSystem/LocalWindowsApplication.h"
#include "../libkvnc_server_log/ClientLogger.h"
#include "../libkvnc_all_logger/LogWriter.h"
#include "../libkvnc_server_config/ConfigReloadListener.h"
#include "../libkvnc_all_util/CommandLineArgs.h"

/**
 * Desktop server application.
 */
class DesktopServerApplication : public LocalWindowsApplication,
                                 public AnEventListener,
                                 public ConfigReloadListener
{
public:
  /**
   * Initializes desktop server.
   * @param appInstance HINSTANCE of application.
   * @throws Exception (or SystemException) on fail.
   * @fixme make command line parsing in this class.
   */
  DesktopServerApplication(HINSTANCE appInstance,
                           const TCHAR *windowClassName,
                           const CommandLineArgs *cmdArgs);

  virtual ~DesktopServerApplication();

  /**
   * Inherited from superclass.
   */
  virtual int run();

protected:
  virtual void onAnObjectEvent();
  virtual void onConfigReload(ServerConfig *serverConfig);

private:
  void freeResources();

  Configurator m_configurator;
  ClientLogger m_clientLogger;
  LogWriter m_log;

  // Transport
  AnonymousPipe *m_clToSrvChan;
  AnonymousPipe *m_srvToClChan;
  BlockingGate *m_clToSrvGate;
  BlockingGate *m_srvToClGate;

  DesktopSrvDispatcher *m_dispatcher;

  // Servers
  UpdateHandlerServer *m_updHandlerSrv;
  UserInputServer *m_uiSrv;
  ConfigServer *m_cfgServer;
  GateKickHandler *m_gateKickHandler;

  SessionChangesWatcher *m_sessionChangesWatcher;
};

#endif // __DESKTOPSERVER_H__
