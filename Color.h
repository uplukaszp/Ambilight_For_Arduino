/*
 * Color.h
 *
 *  Created on: 11.05.2017
 *      Author: Lukasz
 */

#ifndef COLOR_H_
#define COLOR_H_
#include <Arduino.h>
#include "Showable.h"
class Color:public Showable {
public:
	Color(uint8_t r,uint8_t g,uint8_t b,uint8_t pos=-1);
	virtual ~Color();
	char* toString();
	uint8_t getR();
	uint8_t getG();
	uint8_t getB();
	virtual void changeBrightness();
	virtual void show(Adafruit_NeoPixel& leds);
private:
		uint8_t r,g,b;
		static float brightness=1.0f;
		bool isGrowing=true;
		static float step=0.06f;
		uint8_t pos;
};
#endif /* COLOR_H_ */
