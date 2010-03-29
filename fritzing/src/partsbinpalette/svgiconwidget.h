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



#ifndef SVGICONWIDGET_H_
#define SVGICONWIDGET_H_

#include <QGraphicsWidget>
#include <QGraphicsPixmapItem>
#include <QToolTip>
#include <QPointer>

#include "../model/modelpart.h"
#include "../items/itembase.h"

class SvgIconWidgetContainer;

class SvgIconWidget : public QGraphicsWidget
{
Q_OBJECT
public:
	SvgIconWidget(ModelPart *, ViewIdentifierClass::ViewIdentifier, long id, QMenu * itemMenu);
	~SvgIconWidget();
	ItemBase * itemBase() const;
	ModelPart * modelPart() const;
	const QString &moduleID() const;

	static void initNames();
	static void cleanup();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0);
	void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
	void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );

protected:
	QPointer<ItemBase> m_itemBase;
	QGraphicsPixmapItem * m_pixmapItem;
	QString m_moduleId;
};


#endif /* SVGICONWIDGET_H_ */
