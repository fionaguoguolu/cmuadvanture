#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "dusterClass.h"

DusterClass::DusterClass(void)
{
	if (png.Decode("duster.png"))
	{
		png.Flip();
	}
	else
	{
		printf("Error reading duster png.\n");
	}
	Initialize();
}

void DusterClass::Initialize(void)
{
	state = 1;
	x = 50+(int)(rand()%(800-150));
	y = 70+(int)(rand()%(600-100));
	life = 2;
}
	
DusterClass::~DusterClass(void)
{
	CleanUp();
}

void DusterClass::CleanUp(void)
{
	state = 0;
	x = 0;
	y = 0;
	life = 0;
}

bool DusterClass::IsDusterClicked(const int mx, const int my, const int lb) const
{
	bool cursorOver = 0;
	double relativeX = mx - x;
	double relativeY = my - y;
	
	if ((mx>=0) && (mx<800) && (my>=0) && (my<600))
	{
		if((relativeX>=0) && (relativeX<=png.wid) && (relativeY>=-png.hei) && (relativeY<=0))
		{
			cursorOver = 1;
		}
	
		if ((cursorOver==1) && (lb==1))
		{
			return 1;
		}
	}
	return 0;
}

void DusterClass::Display(void) const
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
		printf("Error reading duster png.\n");
	}
}

void DusterClass::SetState(bool newState)
{
	state = newState;
}

bool DusterClass::GetState(void) const
{
	if (state == 1)
	{
		return 1;
	}
	return 0;
} 

bool DusterClass::TimeOut(const int duster_startTime, const int timeNow) const
{
	if ((timeNow-duster_startTime) > life)
	{
		return 1;
	}
	return 0;
} 