#ifndef COLORTABLE_H_
#define COLORTABLE_H_

#include "Color.h"
#include "vector"
#include "Showable.h"
class ColorTable :public Showable{
public:
	ColorTable();
	virtual ~ColorTable();
	virtual void show(Adafruit_NeoPixel& leds);
	Showable* nextColor();
	Showable* currentColor();
	virtual void add(Showable *s);
	virtual void changeBrightness();
private:

	std::vector<Showable*> colorTable;
	int currentI;
};

#endif /* COLORTABLE_H_ */
