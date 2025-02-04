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

#ifndef __DESKTOPSRVDISPATCHER_H__
#define __DESKTOPSRVDISPATCHER_H__

#include "../libkvnc_all_thread/GuiThread.h"
#include "BlockingGate.h"
#include "ClientListener.h"
#include "../libkvnc_all_util/AnEventListener.h"
#include "../libkvnc_all_winSystem/WindowsEvent.h"
#include "../libkvnc_all_logger/LogWriter.h"
#include <map>

class DesktopSrvDispatcher: public GuiThread
{
public:
  DesktopSrvDispatcher(BlockingGate *gate,
                       AnEventListener *m_extTerminationListener,
                       LogWriter *log);
  virtual ~DesktopSrvDispatcher();

  void registerNewHandle(UINT8 code, ClientListener *listener);

protected:
  virtual void execute();
  virtual void onTerminate();
  void notifyOnError();

  BlockingGate *m_gate;

  std::map<UINT8, ClientListener *> m_handlers;

  AnEventListener *m_extErrorListener;

  LogWriter *m_log;
};

#endif // __DESKTOPSRVDISPATCHER_H__
