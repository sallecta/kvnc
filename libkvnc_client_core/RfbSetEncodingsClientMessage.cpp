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

#include "RfbSetEncodingsClientMessage.h"
#include "DecoderStore.h"

RfbSetEncodingsClientMessage::RfbSetEncodingsClientMessage(std::vector<int> *encodings)
{
  m_encodings = *encodings;
}

RfbSetEncodingsClientMessage::~RfbSetEncodingsClientMessage()
{
}

void RfbSetEncodingsClientMessage::send(RfbOutputGate *output)
{
  AutoLock al(output);
  output->writeUInt8(lkvnc_rfb_Defs__Client::SET_ENCODINGS);
  output->writeUInt8(0); // padding 1 byte

  // output count of encoding and out code of all encodings
  output->writeUInt16(static_cast<UINT16>(m_encodings.size()));

  for (std::vector<int>::iterator i = m_encodings.begin();
       i != m_encodings.end();
       i++) {
    output->writeInt32(*i);
  }

  output->flush();
}
