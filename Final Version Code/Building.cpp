#include "Building.h"

Building::Building()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	strcpy(name, "");
}
void Building::set(char iname[], int ix, int iy, int iw, int ih)
{
	strcpy(name, iname);
	x = ix;
	y = iy;
	w = iw;
	h = ih;
}
int Building::getX() const
{
	return x;
}
int Building::getY() const
{
	return y;
}
int Building::getW() const
{
	return w;
}
int Building::getH() const
{
	return h;
}
void Building::getName(char str[])
{
	strcpy(str, name);
}