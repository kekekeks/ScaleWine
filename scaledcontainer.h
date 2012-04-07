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
#ifndef SCALEDCONTAINER_H
#define SCALEDCONTAINER_H

#include <QMainWindow>
#include <QTimer>
class ScaledContainer : public QMainWindow
{
	Q_OBJECT
	Qt::HANDLE xPixmap;
	QPixmap pixmap;
	Qt::HANDLE dirtyMon;
	WId wId;
	QTimer timer;
public:
	explicit ScaledContainer(WId winId);

	virtual void paintEvent(QPaintEvent *ev);
signals:
	
public slots:
	void resetPixmap ();
};

#endif // SCALEDCONTAINER_H
