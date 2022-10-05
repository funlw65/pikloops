/***************************************************************************
                          gqtextedit.h  -  description
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
/* Implements a draggable QTextEdit
   @author Javier Fernando Vargas G */

#ifndef GQTEXTEDIT_H
#define GQTEXTEDIT_H

#include <QMouseEvent>
#include <QTextEdit>
#include <QWidget>


class GQTextEdit : public QTextEdit
{
    Q_OBJECT

public: 
    GQTextEdit (QWidget *parent = 0);
    ~GQTextEdit ();
    virtual void contentsMousePressEvent (QMouseEvent *e);
};

#endif
