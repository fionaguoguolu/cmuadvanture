# include "gear.h"

const double Pi=3.142;

gear::gear(): x(0), y(0),
	theta(0), w(0), N(0), R(0),
	r(0), g(0), b(0) {}

gear::gear(int Ni, double Ri, int ri, int gi, int bi): x(0), y(0),
	theta(0), w(0)
{
	N = Ni;
	R = Ri;
	r = ri;
	g = gi;
	b = bi;
}

void gear::setSpeed(double wi)
{
	w = wi;
}

void gear::setN(int Ni)
{
	N = Ni;
	R = N*10/Pi;
}

void gear::setColor(int ri, int gi, int bi)
{
	r = ri;
	g = gi;
	b = bi;
}
	
void gear::setPosition(double xi, double yi, double thetai)
{
	x = xi;
	y = yi;
	theta = thetai;
}

double gear::getX() const
{
	return x;
}

double gear::getY() const
{
	return y;
}

double gear::getTheta() const
{
	return theta;
}

double gear::getRadius() const
{
	return R;
}

int gear::getN() const
{
	return N;
}

double gear::getSpeed() const
{
	return w;
}

double gear::getRed() const
{
	return r;
}

double gear::getGreen() const
{
	return g;
}

double gear::getBlue() const
{
	return b;
}

void gear::rotate(double dt)
{
	theta += w*dt;
}

void gear::draw()
{
	double d_angle = 0;
	double width = 10;
	double angle = 0;		
	
	// changes by Chun Fan
	// circle	
	glColor3ub(255,255,255);
	glBegin(GL_POLYGON);
	int nSector = (int)(2*Pi*R/2);
	d_angle = 2*Pi/nSector;
	for (int i=0; i<nSector; i++)
		glVertex2d(x + (R+1)*cos(i*d_angle), y + (R+1)*sin(i*d_angle));
	glEnd();
	
	// teeth	
	glColor3ub(r,g,b);
	glBegin(GL_QUADS);
	d_angle = 2*Pi/N;
	for (int i=0; i<N; i++)
	{
		angle = d_angle*i + theta;
		glVertex2d(x + (R+width)*cos(angle) - width/2*sin(angle), 
			y + (R+width)*sin(angle) + width/2*cos(angle));
		glVertex2d(x + (R+width)*cos(angle) - (-width)/2*sin(angle), 
			y + (R+width)*sin(angle) + (-width)/2*cos(angle));
		glVertex2d(x - (-width)/2*sin(angle), y + (-width)/2*cos(angle));
		glVertex2d(x - width/2*sin(angle), y + width/2*cos(angle));
	}
	glEnd();
	
	// changes by Chun Fan
	glColor3ub(255,255,255);
	glBegin(GL_LINE_LOOP);
	
	for (int i=0; i<N; i++)
	{
		angle = d_angle*i + theta;
		glVertex2d(x + (R+width)*cos(angle) - width/2*sin(angle), 
			y + (R+width)*sin(angle) + width/2*cos(angle));
		glVertex2d(x + (R+width)*cos(angle) - (-width)/2*sin(angle), 
			y + (R+width)*sin(angle) + (-width)/2*cos(angle));
		glVertex2d(x - (-width)/2*sin(angle), y + (-width)/2*cos(angle));
		glVertex2d(x - width/2*sin(angle), y + width/2*cos(angle));
	}
	glEnd();
	
	// circle	
	glColor3ub(r,g,b);
	glBegin(GL_POLYGON);
	//int nSector = (int)(2*Pi*R/2);	// changes by Chun Fan
	d_angle = 2*Pi/nSector;
	for (int i=0; i<nSector; i++)
		glVertex2d(x + R*cos(i*d_angle), y + R*sin(i*d_angle));
	glEnd();
	
	// axis	
	glColor3ub(255,255,255);
	glBegin(GL_POLYGON);
	nSector = (int)(2*Pi*5/1);
	d_angle = 2*Pi/nSector;
	for (int i=0; i<nSector; i++)
		glVertex2d(x + 5*cos(i*d_angle), y + 5*sin(i*d_angle));
	glEnd();
}