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

#include "../libkvnc_all_util/inttypes.h"

class lkvnc_rfb_Defs__Client
{
public:
  static const UINT32 BEGIN_NEG = 12;
  static const UINT32 CHAT_REQ = 7;
  static const UINT32 CLIENT_CHAT_MSG = 8;
  static const UINT32 CLIENT_CUT_TEXT = 6;
  static const UINT32 CLIENT_SDP = 10;
  static const UINT32 DISABLE_P2P = 14;
  static const UINT32 ENABLE_P2P = 13;
  static const UINT32 FB_UPDATE_REQUEST = 1;
  static const UINT32 FIX_COLOR_MAP_ENTRIES = 1;
  static const UINT32 KEYBOARD_EVENT = 4;
  static const UINT32 P2P_OK = 15;
  static const UINT32 POINTER_EVENT = 5;
  static const UINT32 SERVER_CHAT_MSG = 9;
  static const UINT32 SERVER_SDP = 11;
  static const UINT32 SET_ENCODINGS = 2;
  static const UINT32 SET_PIXEL_FORMAT = 0;
};

class lkvnc_rfb_Defs__Server
{
public:
  static const UINT32 FB_UPDATE = 0;
  static const UINT32 SET_COLOR_MAP_ENTRIES = 1;
  static const UINT32 BELL = 2;
  static const UINT32 SERVER_CUT_TEXT = 3;
};
