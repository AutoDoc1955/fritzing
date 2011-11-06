/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2011 Fachhochschule Potsdam - http://fh-potsdam.de

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

#include "fileprogressdialog.h"
#include "../debugdialog.h"
#include "../processeventblocker.h"

#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLocale>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QSplashScreen>

/////////////////////////////////////

FileProgressDialog::FileProgressDialog(const QString & title, int initialMaximum, QWidget * parent) : QDialog(parent)
{
	QSplashScreen *splash = NULL;
	foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        splash = qobject_cast<QSplashScreen *>(widget);
		if (splash) {
			break;
		}
	}

	init(title, initialMaximum);
    setModal(splash == NULL);			// OS X Lion doesn't seem to like modal dialogs during splash time

	show();
	if (splash) {
		int offset = (splash->height() / 2) + (this->height() / 2);
		QRect r = this->geometry();
		r.adjust(0, offset, 0, offset);
		this->setGeometry(r);
	}
	ProcessEventBlocker::processEvents();
}

FileProgressDialog::FileProgressDialog(QWidget *parent) : QDialog(parent) 
{
	init(QObject::tr("File Progress..."), 0);
}

void FileProgressDialog::init(const QString & title, int initialMaximum)
{
	Qt::WindowFlags flags = windowFlags();
	flags |= Qt::CustomizeWindowHint;
	flags ^= Qt::WindowCloseButtonHint;
	flags ^= Qt::WindowSystemMenuHint;
	flags ^= Qt::WindowContextHelpButtonHint;
	//flags ^= Qt::WindowTitleHint;
	setWindowFlags(flags);

	this->setWindowTitle(title);

	QVBoxLayout * vLayout = new QVBoxLayout(this);

	m_message = new QLabel(this);
	m_message->setMinimumWidth(300);
	vLayout->addWidget(m_message);

	m_progressBar = new QProgressBar(this);
	m_progressBar->setMinimum(0);
	m_progressBar->setMaximum(initialMaximum);
	vLayout->addWidget(m_progressBar);

    //QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);
	//buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
	//buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);
    //connect(buttonBox, SIGNAL(rejected()), this, SLOT(sendCancel()));
	//vLayout->addWidget(buttonBox);

	this->setLayout(vLayout);
}

FileProgressDialog::~FileProgressDialog() {
}

void FileProgressDialog::setMinimum(int minimum) {
	m_progressBar->setMinimum(minimum);
}

void FileProgressDialog::setMaximum(int maximum) {
	m_progressBar->setMaximum(maximum);
}

void FileProgressDialog::setValue(int value) {
	m_progressBar->setValue(value);
	ProcessEventBlocker::processEvents();
}

int FileProgressDialog::value() {
	return m_progressBar->value();
}

void FileProgressDialog::sendCancel() {
	emit cancel();
}

void FileProgressDialog::closeEvent(QCloseEvent *event)
{
	event->ignore();
}

void FileProgressDialog::setMessage(const QString & message) {
	m_message->setText(message);
	ProcessEventBlocker::processEvents();
}

void FileProgressDialog::setBinLoadingCount(int count) 
{
	m_binLoadingCount = count;
	m_binLoadingIndex = -1;
	m_binLoadingStart = value();
}

void FileProgressDialog::setBinLoadingChunk(int chunk) 
{
	m_binLoadingChunk = chunk;
}

void FileProgressDialog::loadingInstancesSlot(class ModelBase *, QDomElement & instances)
{
	m_binLoadingValue = m_binLoadingStart + (++m_binLoadingIndex * m_binLoadingChunk / (double) m_binLoadingCount);
	setValue(m_binLoadingValue);

	int count = instances.childNodes().count();

	// * 3 comes from: once for model part load, once for list view, once for icon view
	m_binLoadingInc = m_binLoadingChunk / (double) (m_binLoadingCount * 3 * count);
}
		
void FileProgressDialog::loadingInstanceSlot(class ModelBase *, QDomElement & instance)
{
	Q_UNUSED(instance);
	settingItemSlot();
}

void FileProgressDialog::settingItemSlot()
{
	m_binLoadingValue += m_binLoadingInc;
	if ((int) m_binLoadingValue > value()) {
		setValue(m_binLoadingValue);
	}
}

void FileProgressDialog::resizeEvent(QResizeEvent * event)
{
	QDialog::resizeEvent(event);
	QRect scr = QApplication::desktop()->screenGeometry();
	move( scr.center() - rect().center() );
}
