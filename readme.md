# DDS Sine Sweeper #

Copyright 2013 Al Brown

al [at] eartoearoak.com

A sweeping sine signal source based on the [STM8S-Discovery](http://www.st.com/web/en/catalog/tools/FM116/SC959/SS1532/PF247087) and a cheap AD9850 module.
Capable of frequencies from 1Hz to 40MHz (potentially up to 70MHz).  It outputs a 1Vp-p signal and trigger output to synchronise an oscilloscope for quick frequency response testing.

Full details can be found [here](http://eartoearoak.com/hardware/dds-sine-sweeper)


## Usage ##

The hex file is located in the firmware directory and can be flashed using the [ST Visual Programmer](http://www.st.com/web/catalog/tools/FM147/CL1794/SC1807/SS1747/PF210568), the circuit diagram is located in the schematic directory.  Although the Eagle schematic does include footprints these haven't been checked so it's advisable to use breadboard for the construction.

**Navigation**

Use the Left/Right buttons to move between digits and options, the Enter button selects a digit or option.

Options are indicated by a right arrow.

To change the frequency move to the desired digit, press Enter and use the Left/Right buttons to change the digit.  Press Enter again when finished.

To start sweeping use the Left button and move to the arrow, press Enter and use the Left/Right buttons to select a mode.  Press Enter again when finished.

When a sweep mode is selected enter the desired frequency limits, followed by pressing Enter on OK.  The next screen allows you to select the period of the sweep.  Finally start the sweep by selecting OK.

To stop the sweep press Enter which will return to the fixed mode.

**Modes**

- **Fixed** - Output a single fixed frequency (defaults to 10MHz)
- **Ramp sweep** - Sweep from the start to stop frequencies and repeat
- **Triangle sweep** - Sweep from the start to stop frequencies, reverse and repeat
- **Restore defaults** - Restore the firmware default frequencies


## License ##

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.