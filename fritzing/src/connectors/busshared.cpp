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

$Revision$:
$Author$:
$Date$

********************************************************************/

#include "busshared.h"
#include "connectorshared.h"
#include "../debugdialog.h"
#include "connectoritem.h"

BusShared::BusShared(const QDomElement & busElement, const QHash<QString, ConnectorShared *> & connectorHash)
{
	m_id = busElement.attribute("id");
	
	QDomElement connector = busElement.firstChildElement("nodeMember");
	while (!connector.isNull()) {
		QString id = connector.attribute("connectorId");
		if (id.isNull()) continue;
		if (id.isEmpty()) continue;
				
		ConnectorShared * stuff = connectorHash.value(id);
		if (stuff == NULL) continue;
		
		m_connectors.append(stuff);
		stuff->setBus(this);
		
		connector = connector.nextSiblingElement("nodeMember");
	}
	
}

const QString & BusShared::id() {
	return m_id;
}


const QList<ConnectorShared *> & BusShared::connectors() {
	return m_connectors;
}



	