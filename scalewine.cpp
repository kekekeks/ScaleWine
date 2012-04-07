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
#include "scaledcontainer.h"
#include "xutil.h"
ScaleWine *ScaleWine::instance;


QMap<WId, ScaledContainer*> containers;
bool ScaleWine::x11EventFilter(XEvent *ev)

{
	WId id=XUtil::checkDirtyMonitor(ev);
	if(id==0)
		return false;
	if(!containers.contains(id))
		return false;
	containers[id]->update();
	return true;
}

ScaleWine::ScaleWine(int argc, char **argv):QApplication(argc, argv)
{
	instance=this;
}

void ScaleWine::addWindow(WId handle)
{
	ScaledContainer*cont=new  ScaledContainer(handle);
	containers[handle]=cont;
	cont->resetPixmap();
	cont->show();
	cont->update();


}

