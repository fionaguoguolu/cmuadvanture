#ifndef BUILDING_CLASS_IS_INCLUDED
#define BUILDING_CLASS_IS_INCLUDED

#include <string.h>

class Building
{
protected:
	int x;
	int y;
	int w;
	int h;
	char name[256];
public:
	Building();
	void set(char iname[], int ix, int iy, int iw, int ih);
	int getX() const;
	int getY() const;
	int getW() const;
	int getH() const;
	void getName(char str[]);
};

#endif