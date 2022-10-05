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

#include <math.h>

#include "PikDelay.h"


PiKDelay::PiKDelay (double ClkF, double TmDly)
{
    setClockFrequency (ClkF);
    setTimeDelay (TmDly);
    Refresh ();
}

PiKDelay::~PiKDelay ()
{
}

void PiKDelay::Refresh ()
{
    CounterA = CounterB = CounterC = -1;
    Overflow = 0;
    MachineCycleTime = 4.0 / (ClockFrequency * 1000000.0);
    MachineCycles = floor (TimeDelay / MachineCycleTime);

    if (MachineCycles < MACHINE_CYCLE_MIN)
      {
      }
    else if (MachineCycles <= 771.0)
      {
	CounterA = static_cast<int>((MachineCycles / 3.0) - 1.0);
	MachineCycles = 3 * (CounterA + 1);

	// To make gpasm happy
	if (CounterA == 256)
	  CounterA = 0;
      }
    else if (MachineCycles <= 197125.0)
      {
	CounterB = static_cast<int>((MachineCycles + 763.0) / 770.0);
	CounterA = static_cast<int>((MachineCycles + 763.0 - (770.0 * CounterB)) / 3.0);
	MachineCycles = (3.0 * CounterA) + (770.0 * CounterB) - 763.0;

	// To make gpasm happy
	if (CounterA == 256)
	  CounterA = 0;
	if (CounterB == 256)
	  CounterB = 0;
      }
    else if (MachineCycles <= MACHINE_CYCLE_MAX)
      {
	CounterC = static_cast<int>((MachineCycles - 3.0) / 197125.0 + 1.0);
	CounterB = static_cast<int>(((MachineCycles - 3.0) / CounterC + 758.0) / 770.0);
	CounterA = static_cast<int>(((MachineCycles - 3.0) / CounterC + 758.0 - 770.0
				     * CounterB) / 3.0);
	MachineCycles = (3.0 * CounterA + 770.0 * CounterB - 758.0) * CounterC + 3.0;

	// To make gpasm happy
	if (CounterA == 256)
	  CounterA = 0;
	if (CounterB == 256)
	  CounterB = 0;
	if (CounterC == 256)
	  CounterC = 0;
      }
    else
      Overflow = 1;

    TimeDelay = MachineCycles * MachineCycleTime;
}

void PiKDelay::setClockFrequency (double CF)
{
    if (CF > 0)
      ClockFrequency = CF;
    else
      ClockFrequency = 4.00;
}

void PiKDelay::setTimeDelay (double TD)
{
    if (TD >= 0)
      TimeDelay = TD;
    else
      TimeDelay = 1.00;
}

double PiKDelay::getMachineCycles ()
{
    return MachineCycles;
}

double PiKDelay::getTimeDelay ()
{
    return TimeDelay;
}

double PiKDelay::getClockFrequency ()
{
    return ClockFrequency;
}

int PiKDelay::getCounterA ()
{
    return CounterA;
}

int PiKDelay::getCounterB ()
{
    return CounterB;
}

int PiKDelay::getCounterC ()
{
    return CounterC;
}

int PiKDelay::isOverflow ()
{
    return Overflow;
}
