#include <stdio.h>
#include <string.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "score.h"

Score::Score(void)
{
	winHei = 600;
	winWid = 800;

	if(scoreCard.Decode("scoreCard.png"))
    {
        scoreCard.Flip();
    }
    else
    {
        printf("Error loading score card png.\n");
    }	

	for (int i=0; i<4; i++)
	{
		gameCount[i] = 0;
		gamePassed[i] = 0;
	}
	graduate = 0;
}

Score::~Score(void)
{
}

void Score::DrawScoreCard(void)
{
	char *gameName[] = {
		"Pool",
		"CAD",
		"Gear",
		"Keep Awake"};
		
	FsGetWindowSize(winWid, winHei);
	glRasterPos2d(0.0,(double)(winHei-1));
	glDrawPixels(scoreCard.wid,scoreCard.hei,GL_RGBA,GL_UNSIGNED_BYTE,scoreCard.rgba);
	char msg[256];
	glColor3ub(0, 0, 0);	
	for (int i=0; i<4; i++)
	{
		sprintf(msg, "Game %d: %s", i+1, gameName[i]);
		glRasterPos2d(175, 175+i*100);
		YsGlDrawFontBitmap16x24(msg);
		sprintf(msg, "%d trials, %s", gameCount[i], gamePassed[i]?"Passed":"Failed");
		glRasterPos2d(225, 215+i*100);
		YsGlDrawFontBitmap16x24(msg);
	}
}

int Score::setResult(int game, int passed)
{
	if (game>=0 && game<4)
	{
		gameCount[game]++;
		if (gamePassed[game] == 0) 
		{
			gamePassed[game]=passed;
		}
		return 1;
	}
	else
		return -1;
}
	
int Score::getCount(int game)
{
	if (game>=0 && game<4)
		return gameCount[game];
	else
		return -1;
}

int Score::getResult(int game)
{
	if (game>=0 && game<4)
		return gamePassed[game];
	else
		return -1;
}

int Score::getGraduate()
{
	int countSubject=0;
	for (int i=0; i<4; i++)
	{
		countSubject += gamePassed[i];
	}
	if (countSubject>0) //2)
		return 1;
	else
		return 0;
}