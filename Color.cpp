/*
 * Color.cpp
 *
 *  Created on: 11.05.2017
 *      Author: Lukasz
 */

#include "Color.h"
float Color::step;
float Color::brightness;
Color::Color(uint8_t r,uint8_t g,uint8_t b,uint8_t brightness=1.0f,uint16_t pos=-1)
:r(r),g(g),b(b),pos(pos),isGrowing(true)//brightness(brightness),pos(pos),isGrowing(true),step(0.06f)
{}

Color::~Color() {
}

char* Color::toString()
{
			char buff[50];
			char temp[6];
			dtostrf(brightness,4,2,temp);
			sprintf(buff,"R: %d, G: %d, B: %d, BR: %s, POS: %d\n",r,g,b,temp,pos);
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
void Color::show(Adafruit_NeoPixel& leds)
{
	Serial.print(toString());
	if(pos==-1)
	{
		for(int i=0;i<leds.numPixels();i++)
		{
			leds.setPixelColor(i, getR(), getG(), getB());
			leds.show();
			delay(10);
		}
	}
	else
	{
		Serial.print("single pixel\n");
		leds.setPixelColor(pos, getR(), getG(), getB());
		leds.show();
		delay(10);
	}

}

