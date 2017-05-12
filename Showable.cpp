/*
 * Showable.cpp
 *
 *  Created on: 12.05.2017
 *      Author: Lukasz
 */

#include "Showable.h"

Showable::Showable() {
	// TODO Auto-generated constructor stub

}
void Showable::show(Adafruit_NeoPixel& leds)
{
	for(uint8_t i=0;i<leds.numPixels();i++)
	{
		leds.setPixelColor(i, 0);
	}
	leds.show();
}


Showable::~Showable() {
	// TODO Auto-generated destructor stub
}

