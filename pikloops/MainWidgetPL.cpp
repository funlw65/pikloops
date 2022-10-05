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

#include <QComboBox>
#include <QDateTime>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QString>
#include <QTextCursor>
#include <QTextEdit>
#include <QToolTip>
#include <QVBoxLayout>
#include <QValidator>

#include "GQTextEdit.h"
#include "MainWidgetPL.h"


MainWidgetPL::MainWidgetPL (QWidget *parent) : QWidget (parent)
{
    loopValues = new PiKDelay (4.00, 1.00);
    statusMessage = tr("Actual delay: %1 s  (%2 clock cycles).");

    // input
    QGroupBox *grinput = new QGroupBox (tr ("Input data"), this);
    QLabel *hlabel1 = new QLabel (tr ("Frequency (MHz)"), grinput);    
    clock = new QComboBox (grinput);
    QStringList items;
    items << "1.000000" << "2.000000" << "4.000000" << "8.000000" << "10.000000"
	  << "16.000000" << "20.000000" << "24.000000"<< "32.000000" << "40.000000";
    clock->addItems (items);
    clock->setEditable (true);
    clock->setCurrentIndex (2);
    clock->setToolTip ("Select a standard device clock, or type a custom clock frequency.");
        
    QLabel *hlabel2 = new QLabel (tr ("Needed delay (s)"), grinput);
    delay = new QLineEdit ("1", grinput);
    QDoubleValidator *validator = new QDoubleValidator (0., 9999., 6, this);
    delay->setValidator (validator);
    delay->setMinimumWidth (60);
    
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget (hlabel1);
    hbox->addWidget (clock);
    hbox->addSpacing (40);
    hbox->addWidget (hlabel2);
    hbox->addWidget (delay);
    grinput->setLayout (hbox);
    hbox->setSpacing (3);
    hbox->setContentsMargins (6, 6, 6, 6);

    // output
    QGroupBox *groutput = new QGroupBox (tr ("Output data"), this);
    CodeText = new GQTextEdit (groutput);
    CodeText->setToolTip ("Copy and paste this code, or simply drag and drop it to your editor.");
    CodeText->setReadOnly (true);

    cycles = new QLabel (statusMessage
			 .arg (loopValues->getTimeDelay (), 0, 'f', 8)
			 .arg (loopValues->getMachineCycles (), 0, 'f', 0), groutput);
                        
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget (CodeText);
    vbox->addWidget (cycles);
    groutput->setLayout (vbox);
    
    QGridLayout *grid = new QGridLayout;
    grid->addWidget (grinput, 0, 0);
    grid->addWidget (groutput, 1, 0);
    setLayout (grid);
    
    connect (clock, SIGNAL (activated (const QString&)), this,
	     SLOT (ClockChanged (const QString&)));
    connect (delay, SIGNAL (returnPressed ()), this, SLOT (TimeDelayChanged ()));
    connect (delay, SIGNAL (editingFinished ()), this, SLOT (TimeDelayChanged ()));
    
    refreshWidget ();
}

MainWidgetPL::~MainWidgetPL ()
{
}

void MainWidgetPL::refreshWidget ()
{
    // set label names
    QString routineName = tr ("delay_");
    routineName += delay->text ();
    routineName += tr ("_sec");
    QString loopName = routineName + tr ("_loop");
    QString subRoutineName = tr ("sub_delay_");
    subRoutineName += delay->text ();
    subRoutineName += tr ("_sec");
    QString loopSubRoutineName = subRoutineName + tr ("_loop");

    // generate comments
    QString tmpCode = "; ";
    tmpCode += tr ("Delay code generated by PikLoops");
    tmpCode += " (";
    tmpCode += QDateTime::currentDateTime ().toString (tr ("ddd yyyy-MMM-dd hh:mm:ss"));
    tmpCode += ")\n; ";

    tmpCode += QString (tr ("Time Delay = %1s  with  Osc = %2MHz\n\n"))
      .arg (loopValues->getTimeDelay (), 0, 'f', 8)
      .arg (loopValues->getClockFrequency (), 0, 'f', 8);

    tmpCode += routineName;
    tmpCode += "\n";

    if (loopValues->getCounterC () == -1 && loopValues->getCounterB () == -1
	&& loopValues->getCounterA () == -1)
      {
	tmpCode += "\n; ";
	tmpCode += tr ("PikLoops was unable to calculate the delay you requested.\n");
	if (loopValues->isOverflow () == 1)
	  {
	    double maxDelay = (4.0 * MACHINE_CYCLE_MAX) / (loopValues->getClockFrequency ()
							   * 1000000.0);
	    tmpCode += "; ";
	    tmpCode += QString (tr ("The greatest delay you can get don't have to exceed %1s")
				.arg (maxDelay, 0, 'f', 8));
	  }
	else
	  {
	    double minDelay = (4.0 * MACHINE_CYCLE_MIN) / (loopValues->getClockFrequency ()
							   * 1000000.0);
	    tmpCode += "; ";
	    tmpCode += QString (tr ("The lowest delay you can get have to be greater than %1s")
				.arg (minDelay, 0, 'f', 8));
	  }
      }
    else
      {
	if (loopValues->getCounterC () != -1)
	  {
	    tmpCode += QString ("\tmovlw\tD'%1'\n").arg (loopValues->getCounterC (), 0, 10);
	    tmpCode += QString ("\tmovwf\t");
	    tmpCode += QString (tr ("CounterC"));
	    tmpCode += "\n";
	    tmpCode += loopName;
	    tmpCode += "\n";
	    tmpCode += QString ("\tcall\t");
	    tmpCode += subRoutineName;
	    tmpCode += "\n";
	    tmpCode += QString ("\tdecfsz\t");
	    tmpCode += QString (tr ("CounterC"));
	    tmpCode += QString (",1\n\tgoto\t%1\n").arg (loopName);
	    tmpCode += QString ("\treturn\n");
	    tmpCode += "\n";
	    tmpCode += subRoutineName;
	    tmpCode += "\n";
	    tmpCode += QString ("\tmovlw\tD'%1'\n").arg (loopValues->getCounterB (), 0, 10);
	    tmpCode += QString ("\tmovwf\t");
	    tmpCode += QString (tr ("CounterB"));
	    tmpCode += "\n";
	    tmpCode += QString ("\tmovlw\tD'%1'\n").arg (loopValues->getCounterA (), 0, 10);
	    tmpCode += QString ("\tmovwf\t");
	    tmpCode += QString (tr ("CounterA"));
	    tmpCode += "\n";
	    tmpCode += loopSubRoutineName;
	    tmpCode += "\n";
	    tmpCode += QString ("\tdecfsz\t");
	    tmpCode += QString (tr ("CounterA"));
	    tmpCode += QString (",1\n\tgoto\t%1\n").arg (loopSubRoutineName);
	    tmpCode += QString ("\tdecfsz\t");
	    tmpCode += QString (tr ("CounterB"));
	    tmpCode += QString (",1\n\tgoto\t%1\n").arg (loopSubRoutineName);
	    tmpCode += QString ("\treturn\n");
	  }
	else if (loopValues->getCounterB () != -1)
	  {
	    tmpCode += QString ("\tmovlw\tD'%1'\n").arg (loopValues->getCounterB (), 0, 10);
	    tmpCode += QString ("\tmovwf\t");
	    tmpCode += QString (tr ("CounterB"));
	    tmpCode += "\n";
	    tmpCode += QString ("\tmovlw\tD'%1'\n").arg (loopValues->getCounterA (), 0, 10);
	    tmpCode += QString ("\tmovwf\t");
	    tmpCode += QString (tr ("CounterA"));
	    tmpCode += "\n";
	    tmpCode += loopName;
	    tmpCode += "\n";
	    tmpCode += QString ("\tdecfsz\t");
	    tmpCode += QString (tr ("CounterA"));
	    tmpCode += QString (",1\n\tgoto\t%1\n").arg (loopName);
	    tmpCode += QString ("\tdecfsz\t");
	    tmpCode += QString (tr ("CounterB"));
	    tmpCode += QString (",1\n\tgoto\t%1\n").arg (loopName);
	    tmpCode += QString ("\treturn\n");
	  }
	else if (loopValues->getCounterA () != -1)
	  {
	    tmpCode += QString ("\tmovlw\tD'%1'\n").arg (loopValues->getCounterA (), 0, 10);
	    tmpCode += QString ("\tmovwf\t");
	    tmpCode += QString (tr ("CounterA"));
	    tmpCode += "\n";
	    tmpCode += loopName;
	    tmpCode += "\n";
	    tmpCode += QString ("\tdecfsz\t");
	    tmpCode += QString (tr ("CounterA"));
	    tmpCode += QString (",1\n\tgoto\t%1\n").arg (loopName);
	    tmpCode += QString ("\treturn\n");
	  }
      }
    // update status line
    cycles->setText (statusMessage.arg (loopValues->getTimeDelay (), 0, 'f', 8)
		     .arg ((loopValues->getMachineCycles ()), 0, 'f', 0));

    CodeText->setText (tmpCode);
    CodeText->setFocus ();
}

void MainWidgetPL::setValues ()
{
    loopValues->setClockFrequency (clock->currentText ().toDouble ());
    loopValues->setTimeDelay (delay->text ().toDouble ());
    loopValues->Refresh ();
    refreshWidget ();
}

void MainWidgetPL::ClockChanged (const QString& s)
{
    loopValues->setClockFrequency (s.toDouble ());
    loopValues->Refresh ();
    refreshWidget ();
}

void MainWidgetPL::TimeDelayChanged ()
{
    loopValues->setTimeDelay (delay->text ().toDouble ());
    loopValues->Refresh ();
    refreshWidget ();
}

void MainWidgetPL::copyCode ()
{
    CodeText->selectAll ();
    CodeText->copy ();
    QTextCursor cursor = CodeText->textCursor ();
    cursor.clearSelection ();
    
}