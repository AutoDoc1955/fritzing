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

#ifndef SKETCHMODEL_H
#define SKETCHMODEL_H

#include "modelpart.h"
#include "modelbase.h"

#include <QTextStream>
#include <QMultiHash>

class SketchModel : public ModelBase
{

public:
	SketchModel(bool makeRoot);
	SketchModel(ModelPart * root);
	void removeModelPart(ModelPart *);
	ModelPart * findModelPart(const QString & moduleID, long id);
	bool paste(ModelBase * refModel, const QString & filePath, QList<ModelPart *> & modelParts, ModelPart * parent, QHash<QString, QList<long> * > * externalConnectors);
	void walk(ModelPart *, int indent);
	ModelPartTiny * makeTiny(ModelPart * modelPart);

protected:
	ModelPart * findModelPartAux(ModelPart * modelPart, const QString & moduleID, long id);
};

#endif
