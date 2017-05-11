#ifndef COLORTABLE_H_
#define COLORTABLE_H_

#include "Color.h"
#include "vector"
class ColorTable {
public:
	ColorTable();
	virtual ~ColorTable();
	Color& nextColor();
	Color& currentColor();
private:

	std::vector<Color> colorTable;
	int currentI;
};

#endif /* COLORTABLE_H_ */
