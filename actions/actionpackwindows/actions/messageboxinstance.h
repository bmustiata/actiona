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

#ifndef MESSAGEBOXINSTANCE_H
#define MESSAGEBOXINSTANCE_H

#include "actioninstanceexecutionhelper.h"
#include "actioninstance.h"
#include "ifactionvalue.h"

#include <QMessageBox>

namespace Actions
{
	class MessageBoxInstance : public ActionTools::ActionInstance
	{
		Q_OBJECT
		Q_ENUMS(Icon)
		Q_ENUMS(Buttons)
		Q_ENUMS(Result)

	public:
		enum Icon
		{
			None,
			Information,
			Question,
			Warning,
			Error
		};
		enum Buttons
		{
			OkButton,
			YesNoButtons
		};
		enum Result
		{
			Ok,
			Yes,
			No
		};

		MessageBoxInstance(const ActionTools::ActionDefinition *definition, QObject *parent = 0);

		static ActionTools::StringListPair icons;
		static ActionTools::StringListPair buttons;

		void startExecution();
		void stopExecution();

	private:
		QMessageBox::Icon messageBoxIcon(Icon icon) const;

	private slots:
		void buttonClicked();

	public slots:
		MessageBoxInstance::Result messageBox(const QString &text, const QString &title = QString(), Icon icon = None, Buttons buttons = OkButton);

	private:
		QMessageBox *mMessageBox;
		ActionTools::IfActionValue mIfYes;
		ActionTools::IfActionValue mIfNo;

		Q_DISABLE_COPY(MessageBoxInstance)
	};
}

#endif // MESSAGEBOXINSTANCE