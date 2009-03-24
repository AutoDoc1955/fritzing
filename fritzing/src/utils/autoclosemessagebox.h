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

$Revision: 2085 $:
$Author: cohen@irascible.com $:
$Date: 2009-01-06 12:15:02 +0100 (Tue, 06 Jan 2009) $

********************************************************************/

#ifndef AUTOCLOSEMESSAGEBOX_H
#define AUTOCLOSEMESSAGEBOX_H

#include <QMessageBox>
#include <QTimer>

class AutoCloseMessageBox : public QMessageBox
{
Q_OBJECT
public:
	AutoCloseMessageBox(QWidget * parent);
	void autoExec(long ms);
	void autoShow(long ms);

protected:
	void setUp(long ms);
	void mousePressEvent(QMouseEvent *);

protected slots:
	void autoClose();
	void closeEvent(QCloseEvent * event);

protected:
	QTimer * m_closeTimer;

};

#endif
