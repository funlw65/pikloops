/***************************************************************************
 *   Copyright (C) 2004 by JAVIER FERNANDO VARGAS GONZALEZ                 *
 *   JFVARG@linux                                                          *
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
/* @author JAVIER FERNANDO VARGAS GONZALEZ */

#ifndef PIKDELAY_H
#define PIKDELAY_H

#define MACHINE_CYCLE_MIN 6.0
#define MACHINE_CYCLE_MAX 50464002.0


class PiKDelay
{
public:
    PiKDelay (double = 4.00, double = 1.00);
    ~PiKDelay ();
    void setClockFrequency (double);
    void setTimeDelay (double);
    double getMachineCycles ();
    double getTimeDelay ();
    double getClockFrequency ();
    int getCounterA ();
    int getCounterB ();
    int getCounterC ();
    int isOverflow ();
    void Refresh ();

private:
    double ClockFrequency;
    double TimeDelay;
    double MachineCycles;
    double MachineCycleTime;
    int CounterA;
    int CounterB;
    int CounterC;
    int Overflow;
};

#endif
