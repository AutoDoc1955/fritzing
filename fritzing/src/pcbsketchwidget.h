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

$Revision: 1617 $:
$Author: cohen@irascible.com $:
$Date: 2008-11-22 20:32:44 +0100 (Sat, 22 Nov 2008) $

********************************************************************/

#ifndef PCBSKETCHWIDGET_H
#define PCBSKETCHWIDGET_H

#include "sketchwidget.h"

class PCBSketchWidget : public SketchWidget
{
	Q_OBJECT

public:
    PCBSketchWidget(ViewIdentifierClass::ViewIdentifier, QWidget *parent=0);

	void addViewLayers();
	bool canDeleteItem(QGraphicsItem * item);
	bool canCopyItem(QGraphicsItem * item);
	void createJumper();
	void createTrace();
	void excludeFromAutoroute(bool exclude);
	bool ratsAllRouted();
	void selectAllExcludedTraces();
	void makeChangeRoutedCommand(Wire * wire, bool routed, qreal opacity, QUndoCommand * parentCommand);
	void clearRouting(QUndoCommand * parentCommand);
	void updateRatsnestStatus(CleanUpWiresCommand*, QUndoCommand *);
	void forwardRoutingStatusSignal(int netCount, int netRoutedCount, int connectorsLeftToRoute, int jumperCount);
	void addBoard();
	void setCurrent(bool current);
	void initWire(Wire *, int penWidth);
	virtual bool autorouteNeedsBounds();
	virtual bool autorouteCheckWires();
	virtual bool autorouteCheckConnectors();
	virtual bool autorouteCheckParts();
	const QString & traceColor();
	const QString & jumperColor();
	int jumperWidth();
	virtual void ensureTraceLayersVisible();
	virtual void ensureTraceLayerVisible();
	virtual void ensureJumperLayerVisible();
	bool canChainMultiple();
	void setNewPartVisible(ItemBase *);
	virtual void setJumperFlags(ViewGeometry & vg);

public:
	enum CleanType {
		noClean,
		ninetyClean
	};

	CleanType cleanType();

protected:
	void setWireVisible(Wire * wire);
	void makeWires(QList<ConnectorItem *> & partsConnectorItems, QList <Wire *> & ratsnestWires, Wire * & modelWire, RatsnestCommand *);
	// void checkAutorouted();
	ViewLayer::ViewLayerID multiLayerGetViewLayerID(ModelPart * modelPart, QDomElement & layers, QString & layerName);
	bool canChainWire(Wire *);
	void createJumperOrTrace(const QString & commandString, ViewGeometry::WireFlag, const QString & colorString);
	void createOneJumperOrTrace(Wire * wire, ViewGeometry::WireFlag flag, bool allowAny, QList<Wire *> & done, 
								QUndoCommand * & parentCommand, const QString & commandString, const QString & colorString);
	const QColor & getLabelTextColor();
	const QString & hoverEnterPartConnectorMessage(QGraphicsSceneHoverEvent * event, ConnectorItem * item);
	bool modifyNewWireConnections(Wire * dragWire, ConnectorItem * fromOnWire, ConnectorItem * from, ConnectorItem * to, QUndoCommand * parentCommand);
	void setClipEnds(class VirtualWire *);
	ViewLayer::ViewLayerID getWireViewLayerID(const ViewGeometry & viewGeometry);
	ViewLayer::ViewLayerID getDragWireViewLayerID();
	void dealWithRatsnest(long fromID, const QString & fromConnectorID, 
								  long toID, const QString & toConnectorID,
								  bool connect, class RatsnestCommand *, bool doEmit);
	bool dealWithRatsnestAux(ConnectorItem * & from, ConnectorItem * & to,
							long fromID, const QString & fromConnectorID, 
							long toID, const QString & toConnectorID,
							bool connect, class RatsnestCommand *, bool doEmit);
	bool canDropModelPart(ModelPart * modelPart);
	virtual void removeRatsnestWires(QList< QList<ConnectorItem *>* > & allPartConnectorItems, CleanUpWiresCommand *);
	bool reviewDeletedConnections(QSet<ItemBase *> & deletedItems, QHash<ItemBase *, ConnectorPairHash * > & deletedConnections, QUndoCommand * parentCommand);
	bool alreadyRatsnest(ConnectorItem * fromConnectorItem, ConnectorItem * toConnectorItem);
	bool canCreateWire(Wire * dragWire, ConnectorItem * from, ConnectorItem * to);
	bool bothEndsConnected(Wire * wire, ViewGeometry::WireFlags, ConnectorItem * oneEnd, QList<Wire *> & wires, QList<ConnectorItem *> & partConnectorItems);
	Wire * makeOneRatsnestWire(ConnectorItem * source, ConnectorItem * dest, RatsnestCommand *, bool select);
	bool doRatsnestOnCopy();
	void makeRatsnestViewGeometry(ViewGeometry & viewGeometry, ConnectorItem * source, ConnectorItem * dest); 
	void makeWiresChangeConnectionCommands(const QList<Wire *> & wires, QUndoCommand * parentCommand);
	virtual const QColor * getRatsnestColor(); 
	virtual qreal getRatsnestOpacity(Wire *);
	ConnectorItem * lookForBreadboardConnection(ConnectorItem * connectorItem);
	ConnectorItem * findEmptyBusConnectorItem(ConnectorItem * busConnectorItem);
	long makeModifiedWire(ConnectorItem * fromConnectorItem, ConnectorItem * toConnectorItem, BaseCommand::CrossViewType, ViewGeometry::WireFlags, QUndoCommand * parentCommand);
	void modifyNewWireConnectionsAux(ConnectorItem * fromConnectorItem, ConnectorItem * toConnectorItem, QUndoCommand * parentCommand);
	void makeTwoWires(ConnectorItem * originalFromConnectorItem, ConnectorItem * fromConnectorItem,
						ConnectorItem * originalToConnectorItem, ConnectorItem * toConnectorItem, 
						QUndoCommand * parentCommand); 
	ConnectorItem * lookForNewBreadboardConnection(ConnectorItem * connectorItem, ItemBase * & newBreadboard);
	ConnectorItem * findNearestPartConnectorItem(ConnectorItem * fromConnectorItem);
	ConnectorItem * findEmptyBus(ItemBase * breadboard);
	bool bothEndsConnectedAux(Wire * wire, ViewGeometry::WireFlags flag, ConnectorItem * oneEnd, QList<Wire *> & wires, QList<ConnectorItem *> & partConnectorItems, QList<Wire *> & visited);


protected:
	static void calcDistances(Wire * wire, QList<ConnectorItem *> & ends);
	static void clearDistances();
	static int calcDistance(Wire * wire, ConnectorItem * end, int distance, QList<Wire *> & distanceWires, bool & fromConnector0);
	static int calcDistanceAux(ConnectorItem * from, ConnectorItem * to, int distance, QList<Wire *> & distanceWires);

protected:
	int m_netCount;
	int m_netRoutedCount;
	int m_connectorsLeftToRoute;
	int m_jumperCount;
	bool m_addBoard;
	ItemBase * m_addedBoard;
	QString m_jumperColor;
	int m_jumperWidth;
	QString m_traceColor;
	CleanType m_cleanType;
};

#endif
