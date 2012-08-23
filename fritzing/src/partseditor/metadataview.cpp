/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2012 Fachhochschule Potsdam - http://fh-potsdam.de

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

$Revision: 6140 $:
$Author: cohen@irascible.com $:
$Date: 2012-07-04 15:38:22 +0200 (Wed, 04 Jul 2012) $

********************************************************************/


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>

#include "metadataview.h"
#include "hashpopulatewidget.h"


//////////////////////////////////////

/****************************************

TODO:

    don't allow users to enter "family" into properties

****************************************/

//////////////////////////////////////

FocusOutTextEdit::FocusOutTextEdit(QWidget * parent) : QTextEdit(parent)
{

}

FocusOutTextEdit::~FocusOutTextEdit()
{
}

void FocusOutTextEdit::focusOutEvent(QFocusEvent * e) {
	QTextEdit::focusOutEvent(e);
    if (isUndoRedoEnabled()) {
        emit focusOut();
    }
}

//////////////////////////////////////

MetadataView::MetadataView(QWidget * parent) : QScrollArea(parent) 
{
	this->setWidgetResizable(true);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MetadataView::~MetadataView() {

}

void MetadataView::titleEntry() {
    DebugDialog::debug("title entry");
}

void MetadataView::authorEntry() {
    DebugDialog::debug("author entry");
}

void MetadataView::descrEntry() {
    DebugDialog::debug("descr entry");
}

void MetadataView::labelEntry() {
    DebugDialog::debug("label entry");
}

void MetadataView::familyEntry() {
    DebugDialog::debug("family entry");
}

void MetadataView::dateEntry() {
    DebugDialog::debug("date entry");
}

void MetadataView::initMetadata(const QDomDocument & doc) {

    QDomElement root = doc.documentElement();
    QDomElement label = root.firstChildElement("label");
    QDomElement author = root.firstChildElement("author");
    QDomElement descr = root.firstChildElement("description");
    QDomElement title = root.firstChildElement("title");
    QDomElement date = root.firstChildElement("date");
	QStringList readOnlyKeys;

    QHash<QString, QString> tagHash;    
    QDomElement tags = root.firstChildElement("tags");
    QDomElement tag = tags.firstChildElement("tag");
    while (!tag.isNull()) {
        tagHash.insert(tag.text(), "");
        tag = tag.nextSiblingElement("tag");
    }

    QString family;

    QHash<QString, QString> propertyHash;    
    QDomElement properties = root.firstChildElement("properties");
    QDomElement prop = properties.firstChildElement("property");
    while (!prop.isNull()) {
        QString name = prop.attribute("name");
        QString value = prop.text();
        if (name.compare("family", Qt::CaseInsensitive) == 0) {
            family = value;;
        }
        else {
            propertyHash.insert(name, value);
        }

        prop = prop.nextSiblingElement("property");
    }


	QFrame * mainFrame = new QFrame(this);
	mainFrame->setObjectName("metadataMainFrame");
	QVBoxLayout *mainLayout = new QVBoxLayout(mainFrame);
    mainLayout->setSizeConstraint( QLayout::SetMinAndMaxSize );

    QLabel *explanation = new QLabel(tr("This is where you edit the metadata for the part ..."));
    mainLayout->addWidget(explanation);

    QFormLayout * formLayout = new QFormLayout();
    QFrame * formFrame = new QFrame;
    mainLayout->addWidget(formFrame);

    m_titleEdit = new QLineEdit();
    m_titleEdit->setText(title.text());
	connect(m_titleEdit, SIGNAL(editingFinished()), this, SLOT(titleEntry()));
	m_titleEdit->setObjectName("PartsEditorLineEdit");
    m_titleEdit->setStatusTip(tr("Set the part's title"));
    formLayout->addRow(tr("Title"), m_titleEdit);

    m_dateEdit = new QLineEdit();
    m_dateEdit->setText(date.text());
	connect(m_dateEdit, SIGNAL(editingFinished()), this, SLOT(dateEntry()));
	m_dateEdit->setObjectName("PartsEditorLineEdit");
    m_dateEdit->setStatusTip(tr("Set the part's date"));
    m_dateEdit->setEnabled(false);
    formLayout->addRow(tr("Date"), m_dateEdit);

    m_authorEdit = new QLineEdit();
    m_authorEdit->setText(author.text());
	connect(m_authorEdit, SIGNAL(editingFinished()), this, SLOT(authorEntry()));
	m_authorEdit->setObjectName("PartsEditorLineEdit");
    m_authorEdit->setStatusTip(tr("Set the part's author"));
    formLayout->addRow(tr("Author"), m_authorEdit);

    m_descriptionEdit = new FocusOutTextEdit();
    m_descriptionEdit->setText(descr.text());
	connect(m_descriptionEdit, SIGNAL(focusOut()), this, SLOT(descrEntry()));
	m_descriptionEdit->setObjectName("PartsEditorTextEdit");
    m_descriptionEdit->setStatusTip(tr("Set the part's description--you can use simple html (as defined by Qt's Rich Text)"));
    formLayout->addRow(tr("Description"), m_descriptionEdit);

    m_labelEdit = new QLineEdit();
    m_labelEdit->setText(label.text());
	connect(m_labelEdit, SIGNAL(editingFinished()), this, SLOT(labelEntry()));
	m_labelEdit->setObjectName("PartsEditorLineEdit");
    m_labelEdit->setStatusTip(tr("Set the default part label prefix"));
    formLayout->addRow(tr("Label"), m_labelEdit);

    m_familyEdit = new QLineEdit();
    m_familyEdit->setText(family);
	connect(m_familyEdit, SIGNAL(editingFinished()), this, SLOT(familyEntry()));
	m_familyEdit->setObjectName("PartsEditorLineEdit");
    m_familyEdit->setStatusTip(tr("Set the part's family--what other parts is this part related to"));
    m_familyEdit->setEnabled(false);
    formLayout->addRow(tr("Family"), m_familyEdit);

    m_propertiesEdit = new HashPopulateWidget("", propertyHash, readOnlyKeys, NULL, false, this);
	m_propertiesEdit->setObjectName("PartsEditorPropertiesEdit");
    m_propertiesEdit->setStatusTip(tr("Set the part's properties"));
    formLayout->addRow(tr("Properties"), m_propertiesEdit);

    m_tagsEdit = new HashPopulateWidget("", tagHash, readOnlyKeys, NULL, true, this);
	m_tagsEdit->setObjectName("PartsEditorPropertiesEdit");
    m_tagsEdit->setStatusTip(tr("Set the part's tags"));
    formLayout->addRow(tr("Tags"), m_tagsEdit);

    formFrame->setLayout(formLayout);
    mainFrame->setLayout(mainLayout);

    this->setWidget(mainFrame);
}