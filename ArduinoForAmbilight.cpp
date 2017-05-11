#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include "ColorTable.h"
// d3,d4 switch
//d5 data

#define AMMOUNT 36
#define PIN 5
#define UPDATE 0
#define SAVE 1
#define START_ADDRESS 1
#define BUTTON1 10
#define BUTTON2 4
#define DEBUG_MODE 0

void updateRecivedColors();
void saveInEEPROM();
void readFromEEPROM();
void clearBuffer();
void setColor(Color c,unsigned long del);

Adafruit_NeoPixel leds = Adafruit_NeoPixel(AMMOUNT, PIN);
byte data[(3 * AMMOUNT)+1];
ColorTable colors;



void setup() {
  leds.begin();
  leds.show();
  readFromEEPROM();
  updateRecivedColors();
  Serial.begin(250000);

  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(13,OUTPUT);
  clearBuffer();
}

void loop() {
	if(!Serial.available())
	{
		if(digitalRead(BUTTON2))
		{
			#if DEBUG_MODE==1
				Serial.print("btn2\n");
			#endif

			setColor(colors.nextColor(),10);
			delay (500);
			return;
		}
		if(digitalRead(BUTTON1))
		{
			#if DEBUG_MODE==1
				Serial.print("btn1\n");
				Serial.print(colors.currentColor().toString());
			#endif
			colors.currentColor().changeBrightness();
			setColor(colors.currentColor(),0);
			delay(4);
			return;
		}
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
   for (int i = 0; i < (3 * AMMOUNT); i += 3)
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
void readFromEEPROM()
{
  for (int i = 0; i < (3 * AMMOUNT); i ++)
    {
       data[i]=EEPROM.read(START_ADDRESS+i);
    }
}
void clearBuffer()
{
   for (int i = 0; i < 3 * AMMOUNT; i++)
  {
    data[i] = 0;
  }
}

