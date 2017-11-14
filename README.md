# LCDLibrary
Energia CPP library for the 16x2 LCD Shield

This library allows you to use the Midis 16x2 LCD shield with native Energia c++ Sketches. Note it uses Timer 0 as a PWM to control the backlight brightness of the LCD display.

To use download the zip file containing the .ino, .cpp, and .h files and run the LCDLibrary.ino file in Energia. You will see that this project contains the LCDLibrary.cpp and LCDLibrary.h files as separate tabs.

If you wish to use this in your own sketches then you can simply copy the LCDLibrary.cpp and LCDLibrary.h files into the directory of your new sketch and include the LCDLibrary.h in your sketch

\#include "LCDdriver.h"

When using the LCD shield you need to remove the jumper J5, P1.6 that connects P1.6 to LED2 on the Launchpad as P1.6 is used as the I2C Serial Clock (SCL). P1.7 is used as the I2C Serial Data (SDA).

