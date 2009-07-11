/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2009 Fachhochschule Potsdam - http://fh-potsdam.de

Fritzing is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************

$Revision: 3059 $:
$Author: cohen@irascible.com $:
$Date: 2009-06-02 15:49:29 +0200 (Tue, 02 Jun 2009) $

********************************************************************/


#ifndef SYMBOLPALETTEITEM_H
#define SYMBOLPALETTEITEM_H

#include "paletteitem.h"

class SymbolPaletteItem : public PaletteItem 
{
	Q_OBJECT

public:
	SymbolPaletteItem(ModelPart *, ViewIdentifierClass::ViewIdentifier, const ViewGeometry & viewGeometry, long id, QMenu * itemMenu, bool doLabel = true);
	~SymbolPaletteItem();

	ConnectorItem* newConnectorItem(class Connector *connector);
	void busConnectorItems(class Bus * bus, QList<ConnectorItem *> & items);
	qreal voltage();
	void setVoltage(qreal);
	void collectExtraInfoValues(const QString & prop, QString & value, QStringList & extraValues, bool & ignoreValues);
	QString collectExtraInfoHtml(const QString & prop, const QString & value);
	bool canChangeVoltage();

protected:
	void removeMeFromBus();

protected:
	qreal m_voltage;

};

#endif