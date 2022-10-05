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
/* @short Application Main Window
   @author JAVIER FERNANDO VARGAS G <fernandovargas@cable.net.co>
   @version 0.1 */

#ifndef _PIKLOOPS_H_
#define _PIKLOOPS_H_

#include <QMainWindow>

#include "../config.h"
#include "MainWidgetPL.h"


class PiKLoops : public QMainWindow
{
    Q_OBJECT

public:
    // Default Constructor
    PiKLoops ();
    // Default Destructor
    virtual ~PiKLoops ();

public slots:
    void slotCopy ();
    void slotCalculate ();
    void slotAbout ();

protected:
    MainWidgetPL *clientarea;
};

#endif // _PIKLOOPS_H_
