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

#include "ControlPipeName.h"

#include "../libkvnc_all_util/winhdr.h"
#include "../libkvnc_server_app/NamingDefs.h"

#include "../libkvnc_all_winSystem/WTS.h"

void ControlPipeName::createPipeName(bool forService, StringStorage *pipeName, LogWriter *log)
{
  if (forService) {
    pipeName->setString(
      ServerApplicationNames::FOR_SERVICE_CONTROL_APP_PIPE_NAME);
  } else {
    pipeName->format(_T("%s_On_Session_%d"),
      ServerApplicationNames::FOR_APP_CONTROL_APP_SERVICE_PIPE_NAME,
      WTS::getActiveConsoleSessionId(log));
  }
}
