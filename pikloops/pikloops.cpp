/***************************************************************************
 *   Copyright (C) 2004 by JAVIER FERNANDO VARGAS G                        *
 *   fernandovargas@cable.net.co                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>

#include "MainWidgetPL.h"
#include "pikloops.h"


PiKLoops::PiKLoops () : QMainWindow (0)
{

    clientarea = new MainWidgetPL (this);

    setCentralWidget (clientarea);

    QAction *exit = new QAction (QIcon::fromTheme ("application-exit",
						   QIcon (":/icons/22/exit.png")),
				tr ("Exit"), this);
    connect (exit, SIGNAL (triggered ()), qApp, SLOT (closeAllWindows ()));

    QAction *copy = new QAction (QIcon::fromTheme ("edit-copy", QIcon (":/icons/22/copy.png")),
				 tr ("Copy"), this);
    connect (copy, SIGNAL (triggered ()), this, SLOT (slotCopy ()));
    
    QAction *calculate = new QAction (QIcon::fromTheme ("accessories-calculator",
							QIcon (":/icons/22/calculator.png")),
				      tr ("Calculate"), this);
    connect (calculate, SIGNAL (triggered ()), this, SLOT (slotCalculate ()));
    
    QAction *aboutQt = new QAction (QIcon (":/icons/22/qt-logo.png"), tr ("About Qt"), this);
    connect (aboutQt, SIGNAL (triggered ()), qApp, SLOT (aboutQt ()));
    
    QAction *aboutPikloops = new QAction (QIcon::fromTheme ("help-about",
							    QIcon (":/icons/22/chronometer.png")),
					  tr ("About PiKloops"), this);
    connect (aboutPikloops, SIGNAL (triggered ()), this, SLOT (slotAbout ()));

    QToolBar *tb = new QToolBar (this);
    addToolBar (tb);
    tb->addAction (copy);
    tb->addSeparator ();
    tb->addAction (calculate);
    tb->addSeparator ();
    tb->addAction (exit);

    QMenu *actions= menuBar ()->addMenu (tr ("Actions"));
    actions->addAction (copy);
    actions->addAction (calculate);
    actions->addAction (exit);

    QMenu *help = menuBar ()->addMenu (tr ("Help"));
    help->addAction (aboutQt);
    help->addAction (aboutPikloops);

    setWindowIcon (QIcon (":/icons/22/chronometer.png"));
    setMinimumSize (QSize (500, 650));
    setWindowTitle (tr ("PiKloops for Qt5"));
}

PiKLoops::~PiKLoops ()
{
}

void PiKLoops::slotCopy ()
{
    clientarea->copyCode ();
}

void PiKLoops::slotAbout ()
{
    QString text = "<b>Credits :</b> <br><br>"
                   "<i> Javier Fernando Vargas G:</i>  Author (2004).<br>"
                   "<i> William J. Boucher:</i> Author of the original PicLoops for Windows.<br>"
                   "His Calculations Formulas made it possible.<br> "
                   "<i> Alain Gibaud:</i>  Drag'drop support and port to Qt5.<br>";

    QMessageBox::about (this, "PiKLoops 0.2.5", text);
}

void PiKLoops::slotCalculate ()
{
    clientarea->refreshWidget ();
}
