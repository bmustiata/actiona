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

#ifndef CLICKDEFINITION_H
#define CLICKDEFINITION_H

#include "actiondefinition.h"
#include "clickinstance.h"
#include "listparameterdefinition.h"
#include "numberparameterdefinition.h"
#include "positionparameterdefinition.h"
#include "groupdefinition.h"

#include <climits>

namespace ActionTools
{
	class ActionPack;
	class ActionInstance;
}

namespace Actions
{
	class ClickDefinition : public QObject, public ActionTools::ActionDefinition
	{
	   Q_OBJECT
	
	public:
		explicit ClickDefinition(ActionTools::ActionPack *pack)
		: ActionDefinition(pack)
		{
			ActionTools::ListParameterDefinition *action = new ActionTools::ListParameterDefinition("action", tr("Action"), this);
			action->setTooltip(tr("The action to simulate"));
			action->setItems(ClickInstance::actions);
			action->setDefaultValue(ClickInstance::actions.second.at(ClickInstance::ClickAction));
			addElement(action);
	
			ActionTools::ListParameterDefinition *button = new ActionTools::ListParameterDefinition("button", tr("Button"), this);
			button->setTooltip(tr("The button to simulate"));
			button->setItems(ClickInstance::buttons);
			button->setDefaultValue(ClickInstance::buttons.second.at(ClickInstance::LeftButton));
			addElement(button);
	
			ActionTools::PositionParameterDefinition *position = new ActionTools::PositionParameterDefinition("position", tr("Position"), this);
			position->setTooltip(tr("The screen position where to simulate a mouse click"));
			addElement(position);
	
			ActionTools::GroupDefinition *clickGroup = new ActionTools::GroupDefinition("click", tr("Click action"), this);
			clickGroup->setMasterList(action);
			clickGroup->setMasterValues(QStringList() << ClickInstance::actions.first.at(ClickInstance::ClickAction));
	
			ActionTools::NumberParameterDefinition *amount = new ActionTools::NumberParameterDefinition("amount", tr("Amount"), this);
			amount->setTooltip(tr("The amount of clicks to simulate"));
			amount->setMinimum(1);
			amount->setMaximum(INT_MAX);
			amount->setDefaultValue(1);
			clickGroup->addMember(amount);
	
			addElement(clickGroup);
			
			addException(ClickInstance::FailedToSendInputException, tr("Send input failure"));
			addException(ClickInstance::InvalidActionException, tr("Invalid action"));
		}
	
		QString name() const													{ return QObject::tr("Click"); }
		QString id() const														{ return "ActionClick"; }
		Flag flags() const														{ return ActionDefinition::flags() | Official; }
		QString description() const												{ return QObject::tr("Emulates a mouse click"); }
		ActionTools::ActionInstance *newActionInstance() const					{ return new ClickInstance(this); }
		Category category() const												{ return Device; }
		QPixmap icon() const													{ return QPixmap(":/actions/icons/click.png"); }
		bool requirementCheck(QStringList &missingRequirements) const			{ return requirementCheckXTest(missingRequirements); }
	
	private:
		Q_DISABLE_COPY(ClickDefinition)
	};
}

#endif // CLICKDEFINITION_H