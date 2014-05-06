#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "distractionClass.h"

DistractionClass::DistractionClass(void)
{
	Initialize();
}

void DistractionClass::Initialize(void)
{
	state = 1;
	x = 50+(int)(rand()%(800-150));
	y = 70+(int)(rand()%(600-100));
	life = 1+(int)(rand()%3);
	timeStarted = (int)time(NULL);
}

DistractionClass::~DistractionClass(void)
{
	CleanUp();
}

void DistractionClass::CleanUp(void)
{
	state = 0;
	x = 0;
	y = 0;
	life = 0;
	timeStarted = 0;
}

void DistractionClass::Reset(char input[])
{
	Initialize();
	if (png.Decode(input))
	{
		png.Flip();
	}
	else
	{
		printf("Error reading distraction png.\n");
	}
}

bool DistractionClass::IsDistractionClicked(const int mx, const int my, const int lb) const
{
	bool within = 0;
	double relativeX = mx - x;
	double relativeY = my - y;
	
	if((relativeX>=0) && (relativeX<=png.wid) && (relativeY>=-png.hei) && (relativeY<=0))
	{
		within = 1;
	}
	
	if ((within==1) && (lb==1))
	{
		return 1;
	}
	return 0;
}

void DistractionClass::Display(void) const
{
	if (png.rgba != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glDisable(GL_COLOR_MATERIAL);

		glRasterPos2d(x, y);
		glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);

		glDisable(GL_BLEND);
	}
	else
	{
		printf("Error reading distraction png.\n");
	}
}

void DistractionClass::SetState(bool newState)
{
	state = newState;
}

bool DistractionClass::GetState(void) const
{
	if (state == 1)
	{
		return 1;
	}
	return 0;
} 

bool DistractionClass::TimeOut(const int time) const
{
	if ((time-timeStarted) > life)
	{
		return 1;
	}
	return 0;
} 