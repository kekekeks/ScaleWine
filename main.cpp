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
#include "scalewine.h"
#include <QX11Info>
#include <QPixmap>
#include "xutil.h"
#include <X11/Xlib.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xrender.h>



int main(int argc, char *argv[])
{
	ScaleWine a (argc, argv);
	//a.setGraphicsSystem("native");
	Display *dpy=QX11Info::display();
	XUtil::init(dpy);
	WId target=XUtil::selectWindow();
/*
	XCompositeRedirectWindow(dpy, target, CompositeRedirectManual);

	Qt::HANDLE xpixmap = XCompositeNameWindowPixmap(dpy, target);

	QPixmap::fromX11Pixmap(XUtil::getWindowPixmap(target)).save("wtf.png");
*/
	ScaleWine::addWindow(target);


	/*MainWindow w;
	w.show();
	*/
	return a.exec();
}
