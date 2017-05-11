/*
 * Color.h
 *
 *  Created on: 11.05.2017
 *      Author: Lukasz
 */

#ifndef COLOR_H_
#define COLOR_H_
#include <Arduino.h>
class Color {
public:
	Color(uint8_t r,uint8_t g,uint8_t b,uint8_t brightness=1.0f);
	virtual ~Color();
	char* toString();
	uint8_t getR();
	uint8_t getG();
	uint8_t getB();
	void changeBrightness();
private:

		uint8_t r,g,b;
		float brightness;
		bool isGrowing;
		float step;
};

#endif /* COLOR_H_ */
