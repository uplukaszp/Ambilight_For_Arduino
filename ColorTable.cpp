
#include "ColorTable.h"

ColorTable::ColorTable():currentI(0) {

	colorTable.push_back(Color(0,0,0));
	colorTable.push_back(Color(255,0,0));
	colorTable.push_back(Color(0,255,0));
	colorTable.push_back(Color(0,0,255));
	colorTable.push_back(Color(255,255,255));
	colorTable.push_back(Color(255,255,54));
	colorTable.push_back(Color(255,0,255));
	colorTable.push_back(Color(255,255,0));
	colorTable.push_back(Color(147,255,0));
	colorTable.push_back(Color(255,165,0));
}

ColorTable::~ColorTable() {
	colorTable.clear();
}

Color& ColorTable::nextColor()
{
	currentI++;
	if(currentI>=colorTable.size())
	{
		currentI=0;
	}

	return colorTable.at(currentI);
}
Color& ColorTable::currentColor()
{
	return colorTable.at(currentI);
}

