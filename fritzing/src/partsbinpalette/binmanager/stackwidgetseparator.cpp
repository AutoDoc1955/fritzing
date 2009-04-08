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

$Revision: 2776 $:
$Author: merunga $:
$Date: 2009-04-02 13:54:08 +0200 (Thu, 02 Apr 2009) $

********************************************************************/


#include "stackwidgetseparator.h"

StackWidgetSeparator::StackWidgetSeparator(QWidget *parent)
	:QFrame(parent)
{
	setMinimumHeight(10);
}

void StackWidgetSeparator::enterEvent(QEvent *event) {
	expand();
	emit setReceptor(this);
	QFrame::enterEvent(event);
}

void StackWidgetSeparator::leaveEvent(QEvent *event) {
	shrink();
	emit setReceptor(NULL);
	QFrame::leaveEvent(event);
}

void StackWidgetSeparator::expand() {
	setMinimumHeight(200);
	resize(width(),200);
}

void StackWidgetSeparator::shrink() {
	setMinimumHeight(10);
	resize(width(),10);
}


