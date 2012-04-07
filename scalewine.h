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
#ifndef SCALEWINE_H
#define SCALEWINE_H

#include <QApplication>
#include <QMap>

class ScaleWine : public QApplication
{
	Q_OBJECT
public:
	virtual bool x11EventFilter(XEvent *ev);
	static ScaleWine* instance;
	ScaleWine(int argc, char**argv);
	static void addWindow(WId handle);

signals:
	
public slots:

private slots:

};

#endif // SCALEWINE_H
