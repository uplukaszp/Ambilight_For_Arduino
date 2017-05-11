/*
 * Color.cpp
 *
 *  Created on: 11.05.2017
 *      Author: Lukasz
 */

#include "Color.h"

Color::Color(uint8_t r,uint8_t g,uint8_t b,uint8_t brightness=1.0f)
:r(r),g(g),b(b),brightness(brightness),isGrowing(true),step(0.01f)
{}

Color::~Color() {
}

char* Color::toString()
{
			char buff[24];
			sprintf(buff,"R: %d, G: %d, B: %d, BR: %f\n",r,g,b,brightness);
			return buff;
}
uint8_t Color::getR()
{
	return r*brightness;
}
uint8_t Color::getG()
{
	return g*brightness;
}
uint8_t Color::getB()
{
	return b*brightness;
}
void Color::changeBrightness()
{
	if(isGrowing)
	{
		brightness+=step;
		if(brightness>=1.0f)
		{
			brightness=1.0f;
			isGrowing=false;
		}
	}else
	{
		brightness-=step;
		if(brightness<=0.0f)
		{
			brightness=0.0f;
			isGrowing=true;
		}
	}
}
