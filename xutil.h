/*
main.cpp
Author:
	 Nikita Tsukanov <keks9n@gmail.com>

Copyright (c) 2012 Nikita Tsukanov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU  General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU  General Public License for more details.

You should have received a copy of the GNU  General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef XXUTIL_H
#define XXUTIL_H
#include <QWidget>

typedef unsigned long WId;
class XUtil
{
public:
	static void init(void *d);
	static WId selectWindow();
	static Qt::HANDLE getWindowPixmap(WId win);
	static void freePixmap(Qt::HANDLE pixmap);
	static Qt::HANDLE createDirtyMonitor(WId win);
	static WId checkDirtyMonitor (void*ev);
};
#endif // XUTIL_H
