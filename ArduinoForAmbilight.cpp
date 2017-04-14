#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
// d3,d4 switch
//d5 data

#define AMMOUNT 36
#define PIN 5
#define UPDATE 0
#define SAVE 1
#define START_ADDRESS 1
#define BUTTON1 10
#define BUTTON2 4

struct color
{
	color(uint8_t r,uint8_t g,uint8_t b):r(r),g(g),b(b){};
	uint8_t r,g,b;
};


Adafruit_NeoPixel leds = Adafruit_NeoPixel(AMMOUNT, PIN, NEO_GRB + NEO_KHZ800);
byte data[(3 * AMMOUNT)+1];
float brightness=1.0f;
bool isGrowingBrightness=false;
uint8_t currentColor=0;
uint8_t colorCount=10;

const color colors[] ={
		color(0,0,0),
		color(255,0,0),
		color(0,255,0),
		color(0,0,255),
		color(255,255,255),
		color(255,255,54),
		color(255,0,255),
		color(255,255,0),
		color(147,255,0),
		color(255,165,0),

};

void updateColors(color c);
void updateRecivedColors();
void saveInEEPROM();
void readFromEEPROM();
void clearBuffer();
void changeBrightnes();

void setup() {
  leds.begin();
  readFromEEPROM();
  updateRecivedColors();
  Serial.begin(250000);

  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(13,OUTPUT);
  clearBuffer();
}

void loop() {


    if(digitalRead(BUTTON2)==HIGH)
    {

    	updateColors(colors[currentColor]);
    	currentColor++;
    	if(currentColor>=colorCount)
    	{
    		currentColor=0;
    	}
      delay (500);
    }
    if(digitalRead(BUTTON1))
    {
    	changeBrightnes();
    	delay(10);
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

  }


}
void changeBrightnes()
{
	if(isGrowingBrightness)
	{
		brightness+=0.01f;
		if(brightness>=1.0f)
		{
			isGrowingBrightness=false;
		}
	}else
	{
		brightness-=0.01f;
		if(brightness<=0)
		{
			isGrowingBrightness=true;
		}
	}
	updateColors(colors[currentColor]);
	leds.show();
}

void updateColors(color c)
{
	for(int i=0;i<AMMOUNT;i++)
		{
			leds.setPixelColor(i,(uint8_t)c.r*brightness, (uint8_t)c.g*brightness, (uint8_t)c.b*brightness);
		}
		leds.show();
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

