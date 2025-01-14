// Copyright (C) 2013 GlavSoft LLC.
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

#include "ViewerVncAuthHandler.h"
#include "AuthenticationDialog.h"

ViewerVncAuthHandler::ViewerVncAuthHandler(ConnectionData *connectionData)
: m_connectionData(connectionData)
{
//m_connectionData=connectionData;
}

ViewerVncAuthHandler::~ViewerVncAuthHandler()
{
}

void ViewerVncAuthHandler::getPassword(StringStorage *passString)
{
  // get password from ConnectionData or User Interface
  if (!m_connectionData->isSetPassword()) {
    AuthenticationDialog authDialog;
    StringStorage hostname = m_connectionData->getHost();
    authDialog.setHostName(&hostname);
    if (authDialog.showModal()) {
      m_connectionData->setPlainPassword(authDialog.getPassword());
    } else {
      throw AuthCanceledException();
    }
  }
  *passString = m_connectionData->getPlainPassword();
}
