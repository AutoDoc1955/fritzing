/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2010 Fachhochschule Potsdam - http://fh-potsdam.de

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

#ifndef CONNECTORITEM_H
#define CONNECTORITEM_H

#include "nonconnectoritem.h"
#include "connector.h"

#include <QThread>

class ConnectorItem : public NonConnectorItem
{
Q_OBJECT

public:
	ConnectorItem(Connector *, ItemBase* attachedTo);
	~ConnectorItem();

	Connector * connector();
	void connectorHover(class ItemBase *, bool hovering);
	bool connectorHovering();
	void clearConnectorHover();
	void connectTo(ConnectorItem *);
	int connectionsCount();
	void attachedMoved();
	ConnectorItem * removeConnection(ItemBase *);
	void removeConnection(ConnectorItem *, bool emitChange);
	ConnectorItem * firstConnectedToIsh();
	void setTerminalPoint(QPointF);
	QPointF terminalPoint();
	QPointF adjustedTerminalPoint();
	QPointF sceneAdjustedTerminalPoint(ConnectorItem * anchor);
	bool connectedTo(ConnectorItem *);
	const QList< QPointer<ConnectorItem> > & connectedToItems();
	void setHidden(bool hidden);
	void setInactive(bool inactivate);
	ConnectorItem * overConnectorItem();
	void setOverConnectorItem(ConnectorItem *);
	int attachedToItemType();
	ViewLayer::ViewLayerID attachedToViewLayerID();
	ViewIdentifierClass::ViewIdentifier attachedToViewIdentifier();
	const QString & connectorSharedID();
	const QString & connectorSharedName();
	class ErcData * connectorSharedErcData();
	const QString & busID();
	ModelPartShared * modelPartShared();
	ModelPart * modelPart();
	class Bus * bus();
	void tempConnectTo(ConnectorItem * item, bool applyColor);
	void tempRemove(ConnectorItem * item, bool applyColor);
	Connector::ConnectorType connectorType();
	bool chained();
	void saveInstance(QXmlStreamWriter & );
	void writeConnector(QXmlStreamWriter & writer, const QString & elementName);
	bool maleToFemale(ConnectorItem * other);
	bool wiredTo(ConnectorItem *, ViewGeometry::WireFlags);
	void setBaseTooltip(const QString &);
	void clearConnector();
	bool connectionIsAllowed(ConnectorItem * other);
	void prepareGeometryChange();
	void restoreColor(bool doBuses, int busConnectedCount, bool doCross);
	void showEqualPotential(bool show);
	void setHoverColor();
	bool isGrounded();
	ConnectorItem * chooseFromSpec(ViewLayer::ViewLayerSpec);
	bool connectedToWires();
	bool isCrossLayerConnectorItem(ConnectorItem * candidate);
	bool isCrossLayerFrom(ConnectorItem * candidate);
	bool isInLayers(ViewLayer::ViewLayerSpec);
	ConnectorItem * getCrossLayerConnectorItem();
	void displayRatsnest();
	void prepDisplayRatsnest();
	void clearRatsnestDisplay();
	bool marked();
	void setMarked(bool);

protected:
	void hoverEnterEvent( QGraphicsSceneHoverEvent * event );
	void hoverLeaveEvent( QGraphicsSceneHoverEvent * event );
	void hoverMoveEvent( QGraphicsSceneHoverEvent * event );
	void setNormalColor();
	void setConnectedColor();
	void setUnconnectedColor();
	void setColorAux(QBrush brush, QPen pen, bool paint);
	void setColorAux(const QColor &color, bool paint=true);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	void writeTopLevelAttributes(QXmlStreamWriter & writer);
	void writeOtherElements(QXmlStreamWriter & writer);
	void updateTooltip();
    static class Wire * wiredToAux(ConnectorItem * source, ConnectorItem * target, ViewGeometry::WireFlags flags, QList<ConnectorItem *> & visited);
	bool isEverVisible();
	void setHiddenOrInactive();
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
	void displayRatsnest(QList<ConnectorItem *> &);
	bool isConnectedToPart();

protected:
	QPointer<Connector> m_connector;
	QList< QPointer<ConnectorItem> > m_connectedTo;
	QPointF m_terminalPoint;
	QPointer<ConnectorItem> m_overConnectorItem;
	QString m_baseTooltip;
	bool m_connectorHovering;
	bool m_spaceBarWasPressed;
	bool m_hoverEnterSpaceBarWasPressed;
	bool m_checkedEffectively;
	QList<ConnectorItem *>  m_cacheEqualPotentialDisplayItems;
	QList<ConnectorItem *> * m_ratsnestConnectorItems;
	QList<class VirtualWire *> * m_ratsnestWires;
	bool m_ratsnestColorWasNamed;
	bool m_marked;
	
protected:	
	static QList<ConnectorItem *>  m_equalPotentialDisplayItems;

protected:
	static void collectPart(ConnectorItem * connectorItem, QList<ConnectorItem *> & partsConnectors, ViewLayer::ViewLayerSpec);

public:
	static void collectEqualPotential(QList<ConnectorItem *> & connectorItems, bool crossLayers, ViewGeometry::WireFlags skipFlags);
	static void collectParts(QList<ConnectorItem *> & connectorItems, QList<ConnectorItem *> & partsConnectors, bool includeSymbols, ViewLayer::ViewLayerSpec);
	static void clearEqualPotentialDisplay();
	static bool isGrounded(ConnectorItem * c1, ConnectorItem * c2);
	static void collectConnectorNames(QList<ConnectorItem *> & connectorItems, QStringList & connectorNames);
	static class Wire * wiredTo(ConnectorItem * source, ConnectorItem * target, ViewGeometry::WireFlags flags);

public:
	static const QList<ConnectorItem *> emptyConnectorItemList;
};

#endif
