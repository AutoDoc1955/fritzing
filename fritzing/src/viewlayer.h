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

#ifndef VIEWLAYER_H
#define VIEWLAYER_H

#include <QString>
#include <QAction>
#include <QHash>

#include "utils/misc.h"

class ViewLayer : public QObject
{
	Q_OBJECT

public:
	enum ViewLayerID {
		Icon,
		BreadboardBreadboard,
		Breadboard,
		BreadboardWire,
		BreadboardLabel,
		BreadboardNote,
		BreadboardRuler,
		Schematic,
		SchematicWire,
		SchematicTrace,
		SchematicLabel,
		SchematicNote,
		SchematicRuler,
		Board,
		Copper1,
		GroundPlane,
		Copper0,
		Copper0Trace,
		Keepout,
		Vias,
		Soldermask,
		Silkscreen,
		SilkscreenLabel,
		Outline,
		Jumperwires,
		Ratsnest,
		PcbNote,
		PcbRuler,
		UnknownLayer,
		ViewLayerCount
	};

protected:
	static qreal zIncrement;
	static QHash<ViewLayerID, StringPair *> names;

public:
	ViewLayer(ViewLayerID, bool visible, qreal initialZ);
	~ViewLayer();

	void setAction(QAction *);
	QAction* action();
	QString & displayName();
	bool visible();
	void setVisible(bool);
	qreal nextZ();
	ViewLayerID viewLayerID();
	qreal incrementZ(qreal);
	ViewLayer * parentLayer();
	void setParentLayer(ViewLayer *);
	const QList<ViewLayer *> & childLayers();
	bool alreadyInLayer(qreal z);
	void resetNextZ(qreal z);

public:
	static ViewLayerID viewLayerIDFromString(const QString &);
	static ViewLayerID viewLayerIDFromXmlString(const QString &);
	static const QString & viewLayerNameFromID(ViewLayerID);
	static const QString & viewLayerXmlNameFromID(ViewLayerID);
	static void initNames();
	static qreal getZIncrement();
	static void cleanup();

protected:
	bool m_visible;
	ViewLayerID m_viewLayerID;
	QAction* m_action;
	qreal m_nextZ;
	qreal m_initialZ;
	QList<ViewLayer *> m_childLayers;
	ViewLayer * m_parentLayer;

};


typedef QHash<ViewLayer::ViewLayerID, ViewLayer *> LayerHash;

Q_DECLARE_METATYPE( ViewLayer* );

#endif
