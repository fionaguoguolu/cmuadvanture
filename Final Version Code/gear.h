#ifndef GEAR_CLASS_IS_INCLUDED
#define GEAR_CLASS_IS_INCLUDED

#include <math.h>
#include "fssimplewindow.h"

extern const double Pi;

class gear
{
protected:
	double x, y, theta;
	int N;
	double R;
	double w;
	int r, g, b;
	
public:
	gear();
	gear(int Ni, double Ri, int ri, int gi, int bi);
	void setSpeed(double wi);
	void setN(int Ni);
	void setColor(int ri, int gi, int bi);
	void setPosition(double xi, double yi, double thetai);
	double getX() const;
	double getY() const;
	double getTheta() const;
	double getRadius() const;
	int getN() const;
	double getSpeed() const;
	double getRed() const;
	double getGreen() const;
	double getBlue() const;
	void rotate(double dt);
	void draw();
};

#endif