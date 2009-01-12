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

#ifndef RENDERERVIEWTHING_H
#define RENDERERVIEWTHING_H

#include <QHash>
#include <QSvgRenderer>
#include <QXmlStreamReader>

#include "viewlayer.h"

typedef QHash<ViewLayer::ViewLayerID, class FSvgRenderer *> RendererHash;

class FSvgRenderer : public QSvgRenderer
{
public:
	FSvgRenderer(QObject * parent = 0);

	bool load(const QString & filename);
	bool load ( const QByteArray & contents, const QString & filename );     // for SvgSplitter loads
	const QString & filename();
	QSizeF defaultSizeF();

public:
	static void set(const QString & moduleID, ViewLayer::ViewLayerID, FSvgRenderer *);
	static FSvgRenderer * getByModuleID(const QString & moduleID, ViewLayer::ViewLayerID);
	static FSvgRenderer * getByFilename(const QString & filename, ViewLayer::ViewLayerID);
	static QPixmap * getPixmap(const QString & moduleID, ViewLayer::ViewLayerID viewLayerID, QSize size);
	static void calcPrinterScale();
	static qreal printerScale();

protected:
	void parseForWidthAndHeight(QXmlStreamReader & xml);

protected:
	QString m_filename;
	QSizeF m_defaultSizeF;

protected:
	static qreal m_printerScale;
	static QHash<QString, RendererHash * > m_filenameRendererHash;
	static QHash<QString, RendererHash * > m_moduleIDRendererHash;
};


#endif
