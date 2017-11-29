/*
 * Showable.h
 *
 *  Created on: 12.05.2017
 *      Author: Lukasz
 */

#ifndef SHOWABLE_H_
#define SHOWABLE_H_
#include <Adafruit_NeoPixel.h>
class Showable {
public:
	Showable();
	virtual void show(Adafruit_NeoPixel& leds);
	virtual void add(Showable *s){};
	virtual ~Showable();
	virtual void changeBrightness(){};
};
#endif /* SHOWABLE_H_ */
