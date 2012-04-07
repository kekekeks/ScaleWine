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
#include "xutil.h"
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xdamage.h>
#include <stdio.h>

Display *dpy;

int damage_event_base;
int damage_error_base;
void XUtil::init(void* d)
{
	if(dpy==0)
		dpy=(Display*)d;
	XDamageQueryExtension(dpy, &damage_event_base, &damage_error_base);
}

WId XUtil::selectWindow()
{

	int status;
	Cursor cursor;
	XEvent event;
	Window target_win = None, root = DefaultRootWindow(dpy);
	int buttons = 0;
	int dummyi;
	unsigned int dummy;

	/* Make the target cursor */
	cursor = XCreateFontCursor(dpy, XC_crosshair);

	/* Grab the pointer using target cursor, letting it room all over */
	status = XGrabPointer(dpy, root, False,
			ButtonPressMask|ButtonReleaseMask, GrabModeSync,
			GrabModeAsync, root, cursor, CurrentTime);
	if (status != GrabSuccess) {
		fputs("ERROR: Cannot grab mouse.\n", stderr);
		return 0;
	}

	/* Let the user select a window... */
	while ((target_win == None) || (buttons != 0)) {
		/* allow one more event */
		XAllowEvents(dpy, SyncPointer, CurrentTime);
		XWindowEvent(dpy, root, ButtonPressMask|ButtonReleaseMask, &event);
		switch (event.type) {
			case ButtonPress:
				if (target_win == None) {
					target_win = event.xbutton.subwindow; /* window selected */
					if (target_win == None) target_win = root;
				}
				buttons++;
				break;
			case ButtonRelease:
				if (buttons > 0) /* there may have been some down before we started */
					buttons--;
				break;
		}
	}

	XUngrabPointer(dpy, CurrentTime);      /* Done with pointer */

	if (XGetGeometry (dpy, target_win, &root, &dummyi, &dummyi,
				&dummy, &dummy, &dummy, &dummy) && target_win != root) {
		target_win = XmuClientWindow (dpy, target_win);
	}

	return(target_win);
}

Qt::HANDLE XUtil::getWindowPixmap(WId win)
{
	XCompositeRedirectWindow(dpy, win, CompositeRedirectManual);
	return XCompositeNameWindowPixmap(dpy, win);

}

void XUtil::freePixmap(Qt::HANDLE pixmap)
{
	XFreePixmap(dpy, pixmap);
}

Qt::HANDLE XUtil::createDirtyMonitor(WId win)
{
	return ::XDamageCreate(dpy, win, XDamageReportNonEmpty);
}

WId XUtil::checkDirtyMonitor(void *ev)
{
	XEvent *xev=(XEvent*)ev;
	if(xev->type==XDamageNotify+damage_event_base)
	{
		XDamageNotifyEvent *e=(XDamageNotifyEvent*)ev;
		XDamageSubtract(dpy, e->damage, None, None);
		return e->drawable;
	}
	return 0;
}


