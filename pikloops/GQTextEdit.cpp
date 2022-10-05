/***************************************************************************
                          gqtextedit.cpp  -  description
                             -------------------
    begin                : Sun Sep 19 2004
    copyright            : (C) 2004 by Javier Fernando Vargas G
    email                : fernandovargas@cable.net.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <iostream>
using namespace std;

#include <QApplication>
#include <QClipboard>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QPixmap>

#include "GQTextEdit.h"


GQTextEdit::GQTextEdit (QWidget *parent) : QTextEdit (parent)
{
}

GQTextEdit::~GQTextEdit ()
{
}

void GQTextEdit::contentsMousePressEvent (__attribute__ ((unused)) QMouseEvent *event)
{
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText (QApplication::clipboard ()->text (QClipboard::Selection));
    drag->setMimeData (mimeData);
    drag->setPixmap (QPixmap (":/icons/16/chronometer.png"));
    drag->setHotSpot (QPoint (-20, -20));
    drag->exec (Qt::CopyAction);
}
