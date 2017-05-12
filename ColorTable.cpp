
#include "ColorTable.h"

ColorTable::ColorTable():currentI(0) {

}

ColorTable::~ColorTable() {
	colorTable.clear();
}
void ColorTable::show(Adafruit_NeoPixel& leds)
{
	Serial.print("show in colorTable ");
	Serial.print(colorTable.size());
	Serial.print("\n");
	for(int i=0;i<colorTable.size();i++)
	{
		colorTable[i]->show(leds);
	}
}

Showable* ColorTable::nextColor()
{
	currentI++;
	if(currentI>=colorTable.size())
	{
		currentI=0;
	}

	return colorTable.at(currentI);
}
Showable* ColorTable::currentColor()
{
	return colorTable.at(currentI);
}
void ColorTable::changeBrightness()
{
	for(int i=0;i<colorTable.size();i++)
	{
		colorTable[i]->changeBrightness();
	}
}
void ColorTable::add(Showable *s)
{
	colorTable.push_back(s);
}
