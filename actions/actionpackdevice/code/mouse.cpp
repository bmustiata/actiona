/*
	Actionaz
	Copyright (C) 2008-2010 Jonathan Mercier-Ganady

	Actionaz is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Actionaz is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

	Contact : jmgr@jmgr.info
*/

#include "mouse.h"
#include "mousedevice.h"
#include "code/point.h"

#include <QScriptValueIterator>

namespace Code
{
	QScriptValue Mouse::constructor(QScriptContext *context, QScriptEngine *engine)
	{
		Mouse *mouse = new Mouse;

		QScriptValueIterator it(context->argument(0));

		while(it.hasNext())
		{
			it.next();
			
			//TODO
			//if(it.name() == "mode")
			//	mouse->setModePrivate(context, static_cast<Mode>(it.value().toInt32()));
		}

		return engine->newQObject(mouse, QScriptEngine::ScriptOwnership);
	}
	
	Mouse::Mouse()
		: QObject(),
		QScriptable(),
		mMouseDevice(new MouseDevice)
	{
	}

	void Mouse::setCursorPosition() const
	{
		mMouseDevice->setCursorPosition(Point::parameter(context()));
	}
}