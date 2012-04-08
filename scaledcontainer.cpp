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

class ScaledContainer::Viewport:public QWidget
{
	ScaledContainer *parent;

	virtual void focusInEvent(QFocusEvent *)
	{
		XUtil::setInputFocus(parent->wId);
	}
	virtual void paintEvent(QPaintEvent *ev)
	{
		if(parent->xPixmap==0)
			return;
		QPainter painter(this);
		painter.drawPixmap(0,0, width(), height(), parent->pixmap, 0,0, parent->pixmap.width(), parent->pixmap.height());

	}
	virtual bool x11Event(XEvent *ev)
	{
		XUtil::tryRedirectEvent(ev, parent->wId, parent->sx, parent->sy);
	}

public:
	Viewport(ScaledContainer *parent):QWidget(parent)
	{
		this->parent=parent;
		this->winId();//Force it to create window
	}
};

ScaledContainer::ScaledContainer(WId winId) :
	QMainWindow(0)
{
	pixmap=0;
	xPixmap=0;
	wId=winId;
	dirtyMon = XUtil::createDirtyMonitor(winId);
	timer.start(1000);
	connect(&timer,SIGNAL(timeout()),SLOT(resetPixmap()));
	XUtil::reparentWindow(wId, this->winId());
	vp=new Viewport(this);
	vp->resize(width(), height());
	vp->move(0,0);
	vp->show();
}

void ScaledContainer::resizeEvent(QResizeEvent *ev)
{
	updateScale();
	vp->resize(ev->size());
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
		updateScale();
		pixmap.save("wtf.png");
	}


}



bool ScaledContainer::event(QEvent *event)
{
	if(event->type()==QEvent::WindowActivate)
		XUtil::setInputFocus(wId);
	return QMainWindow::event(event);
}

void ScaledContainer::updatePixmap()
{
	vp->update();
}

void ScaledContainer::updateScale()
{
	if(xPixmap!=0)
	{
		sx=(double)pixmap.width()/(double)width();
		sy=(double)pixmap.height()/(double)height();
	}
}

