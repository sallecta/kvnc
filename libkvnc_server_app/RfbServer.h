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

#ifndef __RFB_SERVER_H__
#define __RFB_SERVER_H__

#include "RfbClientManager.h"
#include "../libkvnc_all_thread/Thread.h"
#include "../libkvnc_all_network/TcpServer.h"
#include "../libkvnc_all_region/Rect.h"

#include "../libkvnc_server_app/ChatDialog.h"
#include "../libkvnc_server_app/FTStatusDialog.h"



/**
 * TCP Server that accepts connections and pases them to RfbClientManager.
 * @see RfbClientManager class.
 * @author enikey.
 */
class RfbServer : public TcpServer
{
public:
  /**
   * Creates new rfb server and starts listening thread.
   * @param bindHost host to bind server.
   * @param bindPort port to bind server.
   * @param clientManager handler for incoming connections.
   * @param viewPort [optional] view port shared by this server.
   * @param lockAddr determinates if serever must set exclusive address usage.
   * if not set, then view port is full screen.
   * @throws Exception when failed to create tcp server.
   */
  RfbServer(const TCHAR *bindHost, unsigned short bindPort,
            RfbClientManager *clientManager,
            bool lockAddr,
            LogWriter *log,
            const Rect *viewPort = 0);
  /**
   * Stops listening thread and deletes rfb server.
   */
  virtual ~RfbServer();

protected:
  /**
   * Inherited from superclass.
   * Checks firewall rules (@see ServerConfig class) for incoming connection
   * and, if it firewall passes connection, when pass it for owning to rfb client manager.
   */
  virtual void onAcceptConnection(SocketIPv4 *socket);

protected:
  /**
   * Owner for connections that passed built in rfb server firewall check.
   */
  RfbClientManager *m_clientManager;

  /**
   * View port for server.
   */
  ViewPortState m_viewPort;

  ChatDialog m_chatDialog;
  FTStatusDialog m_ftsDialog;

private:
  LogWriter *m_log;
};

#endif // __LISTENTCPSOCKET_H__
