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

#ifndef CONNECTORSHARED_H
#define CONNECTORSHARED_H

#include <QString>
#include <QDomElement>
#include <QMultiHash>

#include "../viewlayer.h"
#include "connector.h"


struct SvgIdLayer {
	QString m_svgId;
	QString m_terminalId;
	ViewLayer::ViewLayerID m_viewLayerID;
	bool m_visible;
	bool m_processed;
	QRectF m_rect;		
	QPointF m_point;	
	qreal m_radius;
	qreal m_strokeWidth;
};

class ConnectorShared : public QObject
{
Q_OBJECT

public:
	ConnectorShared();
	ConnectorShared(const QDomElement & domElement);
	~ConnectorShared();

	const QString & id();
	void setId(QString id);
	const QString & description();
	void setDescription(QString description);
	const QString & name();
	void setName(QString name);
	const QString & connectorTypeString();
	void setConnectorType(QString type);
	Connector::ConnectorType connectorType();

	const QMultiHash<ViewIdentifierClass::ViewIdentifier,SvgIdLayer *> &pins();
	const QString pin(ViewIdentifierClass::ViewIdentifier, ViewLayer::ViewLayerID viewLayerID);
	const QString terminal(ViewIdentifierClass::ViewIdentifier viewId, ViewLayer::ViewLayerID viewLayerID);
	SvgIdLayer * fullPinInfo(ViewIdentifierClass::ViewIdentifier viewId, ViewLayer::ViewLayerID viewLayerID);
	void addPin(ViewIdentifierClass::ViewIdentifier layer, QString connectorId, ViewLayer::ViewLayerID, QString terminalId);
	void removePins(ViewIdentifierClass::ViewIdentifier layer);

	class BusShared * bus();
	void setBus(class BusShared *);
	const QString & busID();
	class ErcData * ercData();

protected:
	void loadPins(const QDomElement & domElement);
	void loadPin(QDomElement elem, ViewIdentifierClass::ViewIdentifier viewId);

	QString m_description;
	QString m_id;
	QString m_name;
	QString m_typeString;
	Connector::ConnectorType m_type;
	QString m_ercType;
	class ErcData * m_ercData;
	class BusShared * m_bus;

	QMultiHash<ViewIdentifierClass::ViewIdentifier, SvgIdLayer*> m_pins;
};

static QList<ConnectorShared *> ___emptyConnectorSharedList___;

#endif