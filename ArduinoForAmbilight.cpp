#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include "ColorTable.h"
#define AMMOUNT 36
#define PIN 5
#define UPDATE 0
#define SAVE 1
#define START_ADDRESS 50
#define BUTTON1 10
#define BUTTON2 4


void updateRecivedColors();
void saveInEEPROM();
ColorTable* readFromEEPROM();
void clearBuffer();
void setColor(Color c,unsigned long del);

Adafruit_NeoPixel leds = Adafruit_NeoPixel(AMMOUNT, PIN);
byte data[(3 * AMMOUNT)+1];
ColorTable colors;

void setup() {

  leds.begin();
  leds.show();
  Serial.begin(250000);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(13,OUTPUT);
  clearBuffer();

  colors.add(readFromEEPROM());
  colors.add(new Color(0,0,0));
  colors.add(new Color(255,0,0));
  colors.add(new Color(0,255,0));
  colors.add(new Color(0,0,255));
  colors.add(new Color(255,255,255));
  colors.add(new Color(255,255,54));
  colors.add(new Color(255,0,255));
  colors.add(new Color(255,255,0));
  colors.add(new Color(147,255,0));
  colors.add(new Color(255,165,0));
  colors.currentColor()->show(leds);


  //updateRecivedColors();
}

void loop() {
	if(digitalRead(BUTTON2))
	{
		colors.nextColor()->show(leds);
		delay (500);
		return;
	}
	if(digitalRead(BUTTON1))
	{
		colors.changeBrightness();
		colors.currentColor()->show(leds);
		return;
	}
	if(Serial.available())
	{
		Serial.readBytes(data, (3 * AMMOUNT)+1);
		if(data[3*AMMOUNT]==SAVE)
		{
			saveInEEPROM();
		}
		if(data[3*AMMOUNT]==UPDATE)
		{
			updateRecivedColors();
		}
    return;
  }
}



void setColor(Color c,unsigned long del)
{
	for(int i=0;i<AMMOUNT;i++)
	{
		leds.setPixelColor(i, c.getR(), c.getG(),c.getB());
		delay(del);
		leds.show();
	}
}
void updateRecivedColors()
{
   for (int i = 0; i < (3 * AMMOUNT-1); i += 3)
    {
      leds.setPixelColor(i / 3, data[i], data[i + 1], data[i + 2]);
    }
    leds.show();
}
void saveInEEPROM()
{
    for (int i = 0; i < (3 * AMMOUNT); i ++)
    {
        EEPROM.update(START_ADDRESS+i,data[i]);
    }
}

ColorTable* readFromEEPROM()
{
	ColorTable *c=new ColorTable();
	uint8_t r,g,b,pos;
	pos=0;
	for (int i = 0; i < (3* AMMOUNT); i+=3)
    {
		r=EEPROM.read(START_ADDRESS+i);
		g=EEPROM.read(START_ADDRESS+i+1);
		b=EEPROM.read(START_ADDRESS+i+2);
		c->add(new Color(r,g,b,pos));
		pos++;
    }
	return c;
}
void clearBuffer()
{
   for (int i = 0; i < 3 * AMMOUNT; i++)
  {
    data[i] = 0;
  }
}

