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
#include "scaledcontainer.h"
#include <QPaintEvent>
#include <QPainter>
#include "xutil.h"
ScaledContainer::ScaledContainer(WId winId) :
	QMainWindow(0)
{
	pixmap=0;
	xPixmap=0;
	wId=winId;
	dirtyMon = XUtil::createDirtyMonitor(winId);
	timer.start(1000);
	connect(&timer,SIGNAL(timeout()),SLOT(resetPixmap()));
}

void ScaledContainer::resetPixmap()
{
	if(xPixmap!=0)
	{
		XUtil::freePixmap(xPixmap);
		xPixmap=0;
	}
	xPixmap=XUtil::getWindowPixmap(wId);

	if(xPixmap!=0)
	{
		pixmap=QPixmap::fromX11Pixmap(xPixmap);
		pixmap.save("wtf.png");
	}


}

void ScaledContainer::paintEvent(QPaintEvent *ev)
{
	if(xPixmap==0)
		return;
	QPainter painter(this);
	painter.drawPixmap(0,0, width(), height(), pixmap, 0,0, pixmap.width(), pixmap.height());

}

