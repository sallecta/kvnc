// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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

#ifndef _RECT_H_
#define _RECT_H_

#include "../libkvnc_all_util/CommonHeader.h"
#include "../libkvnc_all_util/StringStorage.h"
#include "../libkvnc_all_region/Rect.h"

class PortMappingRect : public Rect
{
public:
  PortMappingRect(int left, int right, int top, int bottom);
  PortMappingRect();
  virtual ~PortMappingRect();

  // Converts this rect to string value.
  void toString(StringStorage *string) const;

  // Returns true if string can be parsed to rect object,
  // false otherwise.
  static bool tryParse(const TCHAR *string);

  // Parsed string and sets parsed values to output rect.
  // Returns true if string is valid, false otherwise.
  // Remark: "out" parameter can be null.
  static bool parse(const TCHAR *string, PortMappingRect *out);
};

#endif
