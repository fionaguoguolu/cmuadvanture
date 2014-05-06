#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "textInput.h"
#include "questionClass.h"
#include "dusterClass.h"
#include "distractionClass.h"
#include "keepAwake.h"

KeepAwake::KeepAwake(void)
{
	Initialize();
}

KeepAwake::~KeepAwake(void)
{
	YY_passKeepAwake = 0;
	startTime = 0;

	nCorrectQn = 0;
	nDusterCaught = 0;

	delete [] questions;
	delete [] dPNG;
	delete [] distractions;
}

void KeepAwake::Initialize(void)
{
	YY_passKeepAwake = 0;
	startTime = 0;

	nCorrectQn = 0;
	nDusterCaught = 0;

	duster.Initialize();

	LoadBkgd();
	LoadGameMenu();

	questions = new QuestionClass [YY_NQUESTION];
	LoadQuestions();

	dPNG = new char* [YY_NPNG];
	LoadDistractionsPNG();
	
	distractions = new DistractionClass [YY_NDISTRACTION];
	FsPassedTime();
	LoadDistractionClass();
	
	LoadSojiPNG();
}

void KeepAwake::LoadBkgd(void)
{
	if(bkgd.Decode("blackboard.png"))
    {
        bkgd.Flip();
    }
    else
    {
        printf("Error loading background png.\n");
    }	
}

void KeepAwake::LoadGameMenu(void)
{
	if(play.Decode("play.png"))
    {
        play.Flip();
    }
    else
    {
        printf("Error loading play png!\n");
    }	
}

void KeepAwake::LoadQuestions(void)
{	
	char *q = NULL;
	char *a = NULL;

	//all answers in uppercase
	
	q = "C is an object-oriented programming language. T/F?";
	a = "F";
	questions[0].Set(q,a);

	q = "Which smiley emoticon was invented in CMU by Professor Scott Fahlman?";
	a = ":-)";
	questions[1].Set(q,a);

	q = "10 deg C is how many deg F? (integer)";
	a = "50";
	questions[2].Set(q,a);

	q = "A central angle of a circle is how many times that of an inscribed angle?";
	a = "2";
	questions[3].Set(q,a);

	q = "In alpha blending, alpha specifies the solidness of the color. T/F?";
	a = "T";
	questions[4].Set(q,a);

	q = "Who was the author of Brave New World? (1)Dan Brown (2)Aldous Huxley (3)George Orwell ";
	a = "2";
	questions[5].Set(q,a);

	q = "If there are 12 apples, 8 oranges and 16 pears. What is the probability of randomly choosing an orange (simplest fraction)?";
	a = "2/9";
	questions[6].Set(q,a);

	q = "If a picture has 17 by 24 pixels, what is the index of the R value of the pixel at the 9th col of the 4th row?";
	a = "236";
	questions[7].Set(q,a);

	q = "Orion constellation was named after a ___ in Greek mythology.";
	a = "HUNTER";
	questions[8].Set(q,a);

	q = "The repetitive DNA sequence at the ends of the chromosome is called a ____.";
	a = "TELOMERE";
	questions[9].Set(q,a);
}

void KeepAwake::LoadDistractionsPNG(void)
{
	dPNG[0] = "chalk_blue.png";
	dPNG[1] = "chalk_orange.png";
	dPNG[2] = "chalk_purple.png";
	dPNG[3] = "chalk_white.png";
	dPNG[4] = "gummy_green.png";
	dPNG[5] = "gummy_orange.png";
	dPNG[6] = "gummy_red.png";
	dPNG[7] = "gummy_yellow.png";
	dPNG[8] = "pencil.png";
	dPNG[9] = "sweet.png";
	dPNG[10] = "trash.png";
}

void KeepAwake::RandomSetPNG(const int i, const int r)
{
	int n = (int)((r*1000)%YY_NPNG);
	distractions[i].Reset(dPNG[n]);
}

void KeepAwake::LoadDistractionClass(void)
{
	for(int i=0; i<YY_NDISTRACTION; i++)
	{
		int r = FsPassedTime()%1000;	
		RandomSetPNG(i, r);
		if ((r%4)<=1)
		{
			distractions[i].SetState(0);
		}
	}
}

void KeepAwake::LoadSojiPNG(void)
{
	if (correct1.Decode("correct1.png"))
	{
		correct1.Flip();
	}
	else
	{
		printf("Error reading correct1 png");
	}

	if (correct2.Decode("correct2.png"))
	{
		correct2.Flip();
	}
	else
	{
		printf("Error reading correct2 png");
	}

	if (wrong1.Decode("wrong1.png"))
	{	
		wrong1.Flip();
	}
	else
	{
		printf("Error reading wrong1 png");
	}

	if (wrong2.Decode("wrong2.png"))
	{
		wrong2.Flip();
	}
	else
	{
		printf("Error reading wrong2 png");
	}
}

void KeepAwake::DrawBkgd(void) const
{
	glRasterPos2d(0.0,(double)(600-1));
	glDrawPixels(bkgd.wid,bkgd.hei,GL_RGBA,GL_UNSIGNED_BYTE,bkgd.rgba);
}

void KeepAwake::DrawGameMenu(const int MenuX, const int MenuY)
{
	glRasterPos2d((double)(MenuX-(play.wid/2)-1),(double)(MenuY+(play.hei/2)-1));
	glDrawPixels(play.wid,play.hei,GL_RGBA,GL_UNSIGNED_BYTE,play.rgba); 

	char msg[256];
	msg[255] = 0;

	glColor3ub(255, 255, 255);
	
	strcpy(msg, "Pay attention in class and answer the");
	glRasterPos2d(50, 80);
	YsGlDrawFontBitmap16x24(msg);

	strcpy(msg, "questions. At the same time, stay alert");
	glRasterPos2d(50, 130);
	YsGlDrawFontBitmap16x24(msg);

	strcpy(msg, "for dusters thrown by Soji. Click to catch");
	glRasterPos2d(50, 180);
	YsGlDrawFontBitmap16x24(msg);

	strcpy(msg, "them before they hit you and explode in");
	glRasterPos2d(50, 230);
	YsGlDrawFontBitmap16x24(msg);

	strcpy(msg, "your face!");
	glRasterPos2d(50, 280);
	YsGlDrawFontBitmap16x24(msg);

	strcpy(msg, "You have only 2 minutes! Stay awake!!");
	glRasterPos2d(50, 330);
	YsGlDrawFontBitmap16x24(msg);

	strcpy(msg, "Press Esc to exit.");
	glRasterPos2d(50, 380);
	YsGlDrawFontBitmap16x24(msg);
}

bool KeepAwake::IsPlayButtonClicked(const int MenuX, const int MenuY, const int mx, const int my, const int lb)
{
	bool withinButton = 0;
	double relativeX = mx - MenuX;
	double relativeY = my - MenuY;
	
	if((relativeX>=-(play.wid/2)) && (relativeX<=(play.wid/2)) && (relativeY>=-(play.hei/2)) && (relativeY<=(play.hei/2)))
	{
		withinButton = 1;
	}

	if ((lb == 1) && (withinButton == 1))
	{
		return 1;
	}
	return 0;
}

void KeepAwake::DisplayMsg(const char msg[], const int x, const int y, const int r, const int g, const int b) const
{
	glColor3ub(r,g,b);
	glRasterPos2d(x,y);
	YsGlDrawFontBitmap20x32(msg);
}

void KeepAwake::DrawSoji(const bool correctAnswer) const
{
	if (correctAnswer == 1)
	{
		if (time(NULL)%2 == 0)
		{
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glDisable(GL_COLOR_MATERIAL);
		
			glRasterPos2d(550, 370);
			glDrawPixels(correct1.wid,correct1.hei,GL_RGBA,GL_UNSIGNED_BYTE,correct1.rgba);
				
			glDisable(GL_BLEND);
		}
		else 
		{
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glDisable(GL_COLOR_MATERIAL);
		
			glRasterPos2d(550, 350);
			glDrawPixels(correct2.wid,correct2.hei,GL_RGBA,GL_UNSIGNED_BYTE,correct2.rgba);

			glDisable(GL_BLEND);
		}

	}
	else
	{
		if (time(NULL)%2 == 0)
		{
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glDisable(GL_COLOR_MATERIAL);
		
			glRasterPos2d(350, 500);
			glDrawPixels(wrong1.wid,wrong1.hei,GL_RGBA,GL_UNSIGNED_BYTE,wrong1.rgba);

			glDisable(GL_BLEND);
		}
		else 
		{
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glDisable(GL_COLOR_MATERIAL);
		
			glRasterPos2d(250, 550);
			glDrawPixels(wrong2.wid,wrong2.hei,GL_RGBA,GL_UNSIGNED_BYTE,wrong2.rgba);

			glDisable(GL_BLEND);
		}
	}
}

void KeepAwake::UpdateDistractions(const int mx, const int my, const int lb, const int timeNow)
{
	for (int i=0; i<YY_NDISTRACTION; i++)
	{
		if (distractions[i].GetState() == 1)
		{
			distractions[i].Display();
			if ((distractions[i].IsDistractionClicked(mx, my, lb)==1) || (distractions[i].TimeOut(timeNow)==1))
			{
				distractions[i].SetState(0);
			}
		}
		else
		{
			RandomSetPNG(i, rand());
		}
	}
}

int KeepAwake::UpdateDuster(const int mx, const int my, const int lb, const int duster_startTime, const int timeNow)
{
	duster.Display();

	bool clicked = duster.IsDusterClicked(mx, my, lb);
	bool tout = duster.TimeOut(duster_startTime, timeNow);
	if ((clicked==1) || (tout==1))
	{
		duster.SetState(0);
		
		if (clicked == 1)
		{
			nDusterCaught += 1;
			return 1;
		}

		if (tout==1)
		{
			return 2;
		}
	}
	return 0;
}

void KeepAwake::DrawCircle(const int cx, const int cy, const int rad) 
{
    const double YS_PI=3.1415927;

    glBegin(GL_POLYGON);
    
    int i;
    for(i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32.0;
        double x=(double)cx+cos(angle)*(double)rad;
        double y=(double)cy+sin(angle)*(double)rad;
        glVertex2d(x,y);
    }

    glEnd();
}

int KeepAwake::ExplodeDuster(const int startTime, const int timeNow)
{
	int stage = timeNow-startTime;
	int rad;
	const int x1[] = {300, 400, 500, 250, 350, 450, 550, 300, 400, 500};
	const int y1[] = {200, 200, 200, 300, 300, 300, 300, 400, 400, 400};
	const int x2[] = {250, 400, 550, 125, 325, 525, 625, 250, 400, 550};
	const int y2[] = {150, 150, 150, 300, 300, 300, 300, 450, 450, 450};
	const int x3[] = {200, 400, 500, 100, 300, 500, 700, 200, 400, 500};
	const int y3[] = {100, 100, 100, 300, 300, 300, 300, 500, 500, 500};

	switch(stage)
	{
	case 0:
		rad = 100;
		for (int i=0; i<10; i++)
		{
			DrawCircle(x1[i],y1[i],rad);
		}
		DisplayMsg("Wake up!", 350, 300, 255, 0, 0);
		DisplayMsg("Watch out for the duster!", 200, 350, 255, 0, 0);
		return 1;
		break;

	case 1:
		rad = 150;
		for (int i=0; i<10; i++)
		{
			DrawCircle(x2[i],y2[i],rad);
		}
		DisplayMsg("Wake up!", 350, 300, 255, 0, 0);
		DisplayMsg("Watch out for the duster!", 200, 350, 255, 0, 0);
		return 1;
		break;

	case 2:
		rad = 200;
		for (int i=0; i<10; i++)
		{
			DrawCircle(x3[i],y3[i],rad);
		}
		DisplayMsg("Wake up!", 350, 300, 255, 0, 0);
		DisplayMsg("Watch out for the duster!", 200, 350, 255, 0, 0);
		return 1;
		break;

	default: 
		return 0;
		break;
	}
}

void KeepAwake::Score(void)
{
	if ((((double)nCorrectQn/(double)YY_NQUESTION)>0.5) && (((double)nDusterCaught/(double)YY_NDUSTER)>0.5))
	{
		YY_passKeepAwake = 1;
	}
	else
	{
		YY_passKeepAwake = 0;
	}
}

void KeepAwake::DisplayScore(void)
{
	char strQ[256];
	strQ[255] = 0;
	char strD[256];
	strD[255] = 0;
	sprintf(strQ, "%d questions answered", nCorrectQn);
	sprintf(strD, "%d dusters caught", nDusterCaught);

	glColor3ub(255, 255, 255);
	glRasterPos2d(520, 500);
	YsGlDrawFontBitmap12x16(strQ);

	glRasterPos2d(520, 520);
	YsGlDrawFontBitmap12x16(strD);
}

void KeepAwake::DisplayTime(const int startTime, const int timeNow)
{
	char timeStr[256];
	timeStr[255] = 0;
	sprintf(timeStr, "Time: %d seconds", (timeNow-startTime));

	glColor3ub(255, 255, 255);
	glRasterPos2d(550, 50);
	YsGlDrawFontBitmap12x16(timeStr);
}

void KeepAwake::DisplayFinalScore(void)
{
	char str1[256];
	str1[255] = 0;
	char str2[256];
	str2[255] = 0;
	char str3[256];
	str3[255] = 0;
	char str4[256];
	str4[255] = 0;
	char str5[256];
	str5[255] = 0;
	
	sprintf(str1, "%d out of %d questions answered", nCorrectQn, YY_NQUESTION);
	sprintf(str2, "%d out of %d dusters caught", nDusterCaught, YY_NDUSTER);

	glColor3ub(255, 255, 255);
	glRasterPos2d(50, 80);
	YsGlDrawFontBitmap20x32(str1);

	glRasterPos2d(50, 130);
	YsGlDrawFontBitmap20x32(str2);

	if (GetScore())
	{
		strcpy(str3, "Congratulations! You passed!");
		glRasterPos2d(50, 230);
		YsGlDrawFontBitmap20x32(str3);

		strcpy(str4, "You managed to stay awake!");
		glRasterPos2d(50, 280);
		YsGlDrawFontBitmap20x32(str4);
	}
	else
	{
		strcpy(str3, "You fell asleep too often!");
		glRasterPos2d(50, 230);
		YsGlDrawFontBitmap20x32(str3);

		strcpy(str4, "You failed the class!");
		glRasterPos2d(50, 280);
		YsGlDrawFontBitmap20x32(str4);
	}

	strcpy(str5, "Press Esc to exit!");
	glRasterPos2d(350, 380);
	YsGlDrawFontBitmap20x32(str5);
}

int KeepAwake::GetScore(void) const
{
	return YY_passKeepAwake;
}

void KeepAwake::StartGame(void)
{
	Initialize();

	int key=FSKEY_NULL;
	int gameState = 0;
	int lb=0, mb=0, rb=0, mx=0, my=0;

	bool YY_PLAYCLICKED = 0;
	int MenuX = 800/2;
	int MenuY = 3*600/4;

    while(FSKEY_ESC!=key)
    {
        FsPollDevice();
        key=FsInkey();

		int winWidNew = 800;
		int winHeiNew = 600;
		
		switch (gameState)
		{

		// start menu
		case 0:
			FsGetWindowSize(winWidNew,winHeiNew);
			glViewport(0,0,winWidNew,winHeiNew);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0,(float)winWidNew-1,(float)winHeiNew-1,0,-1,1);

			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

			DrawBkgd();
			DrawGameMenu(MenuX, MenuY);

			FsSwapBuffers();
			FsSleep(50);

			while(!YY_PLAYCLICKED)
			{
				FsPollDevice();
				FsGetMouseEvent(lb, mb, rb, mx, my);
				YY_PLAYCLICKED = IsPlayButtonClicked(MenuX, MenuY, mx, my, lb);

				if (FsInkey()==FSKEY_ESC)
				{
					YY_PLAYCLICKED = 1;
					gameState = 2;
				}
			}
			
			if (gameState!=2)
			{
				gameState = 1;
			}
			break;

		// game play
		case 1:
			PlayGame();
			gameState = 2;
			break;

		// end game
		case 2:
			FsGetWindowSize(winWidNew,winHeiNew);
			glViewport(0,0,winWidNew,winHeiNew);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0,(float)winWidNew-1,(float)winHeiNew-1,0,-1,1);

			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
						
			DrawBkgd();
			
			if (time(NULL)%2 == 0)
			{
				glEnable(GL_TEXTURE_2D);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_BLEND);
				glDisable(GL_COLOR_MATERIAL);
		
				glRasterPos2d(100, 570);
				glDrawPixels(correct1.wid,correct1.hei,GL_RGBA,GL_UNSIGNED_BYTE,correct1.rgba);

				glDisable(GL_BLEND);
			}
			else 
			{
				glEnable(GL_TEXTURE_2D);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_BLEND);
				glDisable(GL_COLOR_MATERIAL);
		
				glRasterPos2d(100, 570);
				glDrawPixels(correct2.wid,correct2.hei,GL_RGBA,GL_UNSIGNED_BYTE,correct2.rgba);

				glDisable(GL_BLEND);
			}

			DisplayFinalScore();

			FsSwapBuffers();
			FsSleep(50);	
			break;

		default:
			printf("Case exceeded in Start()");
			key = FSKEY_ESC;
			break;
		};
    }
}

void KeepAwake::PlayGame(void)
{
	bool keepAwakeTimeOut = 0;
	int winWidNew = 800, winHeiNew = 600;
	TextInput answer;
	
	startTime = (int)time(NULL);
	srand(startTime);

	int displayQnMsg = 0;
	int wrongAns = 0;
	int nQnAnswered = 0;
	int ans_startTime = startTime;
	
	int duster_startTime = startTime;

	int wait = 0;
	int wait_time = 0;
	int wait_startTime = startTime;
	
	int displayHitMsg = 0;
	int hit = 0;
	int hit_startTime = startTime;

	int explode = 0;
	int explode_startTime = startTime;

	FsPollDevice();

	while (((nCorrectQn < YY_NQUESTION) || (nDusterCaught < YY_NDUSTER)) && (keepAwakeTimeOut==0) && (FsInkey()!=FSKEY_ESC))
	{
		int lb=0, mb=0, rb=0, mx=0, my=0;

		int timeNow = (int)time(NULL);
		
		FsPollDevice();
		FsGetMouseEvent(lb, mb, rb, mx, my);
		
		FsGetWindowSize(winWidNew,winHeiNew);
		glViewport(0,0,winWidNew,winHeiNew);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)winWidNew-1,(float)winHeiNew-1,0,-1,1);

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		DrawBkgd();
		
		//--------------blackboard question-------------//

		if((displayQnMsg==1) && (wrongAns!=0))
		{
			DisplayMsg(questions[nQnAnswered-1].GetAnswer(), 50, 100, 255, 0, 0);
			DrawSoji(0);

			if((timeNow-ans_startTime) > 4)
			{
				displayQnMsg = 0;
				wrongAns = 0;
			}
		}
		else
		{
			DrawSoji(1);
		}
		
		if (nQnAnswered < YY_NQUESTION)
		{
			questions[nQnAnswered].PrintQn();
		
			char key = FsInkeyChar();

			if (((key>=' ') && (key<='~')) || (key=='\b'))
			{
				answer.Input(key);
			}
			else if (key == '\r')
			{
				ans_startTime = timeNow;
				displayQnMsg = 1;

				if (questions[nQnAnswered].CheckAnswer(answer.GetString()) == 0)
				{
					wrongAns = 1;
				}
				else
				{
					nCorrectQn += 1;
				}
				nQnAnswered += 1;
				answer.Clear();
			}
			answer.Draw();
		}
		else if (nCorrectQn == YY_NQUESTION)
		{
			DisplayMsg("You are smart!", 50, 150, 255, 255, 255);
			DisplayMsg("You have answered all", 50, 200, 255, 255, 255);
			DisplayMsg("the questions correctly!", 50, 250, 255, 255, 255);
		}

		//--------------distractions-------------//

		UpdateDistractions(mx, my, lb, timeNow);

		//--------------catch the duster-------------//

		if((displayHitMsg==1) && (hit==1))
		{
			DisplayMsg("Caught!", 300, 100, 255, 0, 0);
			
			if((timeNow-hit_startTime) > 4)
			{
				displayHitMsg = 0;
				hit = 0;
			}
		}

		if ((wait==1) && ((timeNow-wait_startTime)>wait_time))
		{
			wait = 0;
			duster.Initialize();
			duster_startTime = timeNow;
		}
		
		if (explode == 1)
		{
			explode = ExplodeDuster(explode_startTime, timeNow);
			if (explode == 0)
			{
				wait = 1;
				wait_time = rand()%10;
				wait_startTime = timeNow;				
			}
		}
		
		if ((duster.GetState()==1) && (nDusterCaught<YY_NDUSTER))
		{
			hit = UpdateDuster(mx, my, lb, duster_startTime, timeNow);
		
			if (hit > 0)
			{
				if (hit == 1)
				{
					displayHitMsg = 1;
					hit_startTime = timeNow;
					
					duster.SetState(0);
					wait = 1;
					wait_time = rand()%10;
					wait_startTime = hit_startTime;
				}
				else if (hit == 2)
				{
					hit = 0;
				
					duster.SetState(0);
					explode = 1;
					explode_startTime = timeNow;
				}
			}
		}
		else if (nDusterCaught == YY_NDUSTER)
		{
			hit = 0;
			DisplayMsg("Good job! All dusters caught!", 50, 550, 255, 255, 255);
		}

		//--------------game update-------------//
		
		if ((time(NULL)-startTime) >= 120)
		{
			keepAwakeTimeOut = 1;
		}

		DisplayScore();
		DisplayTime(startTime, timeNow);

		FsSwapBuffers();
		FsSleep(20);
	}

	Score();
}