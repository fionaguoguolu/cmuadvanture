#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include <math.h>
#include "CAD-head.h"



CADCLASS::CADCLASS()
	:level(0),idx(0),MouseClick(0),
	ConfirmationWindow(Uncalled),ShowAnswer(0),
	terminate(0)
{
	LineState=Draw;
	newline=NULL;
	head=new DoublyLinkedListItem<Lines> *[3];    //3 as three levels.
	tail=new DoublyLinkedListItem<Lines> *[3];
	for(int i=0;i<3;i++)
	{
		head[i]=NULL;
		tail[i]=NULL;
		n[i]=0;
	}
}
CADCLASS::~CADCLASS()
{
	newline=NULL;
	for(int i=0;i<3;i++)
	{
		head[i]=NULL;
		tail[i]=NULL;
	}
}

void CADCLASS::CleanUp()
{
	level=0;
	idx=0;
	MouseClick=0;
	ConfirmationWindow=Uncalled;
	ShowAnswer=0;
	terminate=0;
	LineState=Draw;
	newline=NULL;
	head=new DoublyLinkedListItem<Lines> *[3];    //3 as three levels.
	tail=new DoublyLinkedListItem<Lines> *[3];
	for(int i=0;i<3;i++)
	{
		head[i]=NULL;
		tail[i]=NULL;
		n[i]=0;
	}
}
int CADCLASS::CADMain()
{
	int temp=ReadBackground();
	if(0==temp)
	{
		printf("Question File Load Error.\n");
	}
while(FsInkey()!=FSKEY_ESC && terminate==0)
{
	while(ShowAnswer)
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		int winWid,winHei;
		FsGetWindowSize(winWid,winHei);
		glViewport(0,0,winWid,winHei);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
		glRasterPos2d(0.0,(double)(AnswerPng[level-1].hei-1));
		glDrawPixels(AnswerPng[level-1].wid,AnswerPng[level-1].hei,GL_RGBA,GL_UNSIGNED_BYTE,AnswerPng[level-1].rgba);
		MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
		if( FSMOUSEEVENT_LBUTTONUP!=MouseEvent
			&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
			&& mx>750 && mx<795
			&& my>550 && my<595)
			ShowAnswer=0;
		FsSwapBuffers();
		FsSleep(20);
	}
	
	if(level==0)
	{
		FsPollDevice();
		double d1=233.0/255.0,d2=214.0/255.0,d3=203.0/255.0;
		glClearColor(d1,d2,d3,1.0f);
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		glColor3ub(116,71,48);
		glRasterPos2d(70,100);
		YsGlDrawFontBitmap16x20("Computer-Aided-Design Homework Challenge");
		glRasterPos2d(100,180);
		YsGlDrawFontBitmap16x20("On the next screen, add any lines to");
		glRasterPos2d(100,210);
		YsGlDrawFontBitmap16x20("the 2 dimensional representations of");
		glRasterPos2d(100,240);
		YsGlDrawFontBitmap16x20("the 3 dimensional drawing  necessary");
		glRasterPos2d(100,270);
		YsGlDrawFontBitmap16x20("to complete those drawings.");
		glRasterPos2d(100,320);
		YsGlDrawFontBitmap16x20("There will be 3 levels, on each level");
		glRasterPos2d(100,350);
		YsGlDrawFontBitmap16x20("you need to complete every projection");
		glRasterPos2d(100,380);
		YsGlDrawFontBitmap16x20("in order to receive full credit.");
		glColor3ub(185,122,87);
		glBegin(GL_QUADS);
		glVertex2i(250,425);
		glVertex2i(550,425);
		glVertex2i(550,500);
		glVertex2i(250,500);
		glEnd();
		glColor3ub(233,214,203);
		glRasterPos2d(325,475);
		YsGlDrawFontBitmap16x20("Start Game");

		MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
		if( FSMOUSEEVENT_LBUTTONUP!=MouseEvent
			&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
			&& mx>250 && mx<550
			&& my>425 && my<500)
		{
			level=1;
			idx=0;			
		}
	}
	else if(level==1
		|| level==2
		|| level==3)
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		DrawBackground();
		DrawLines();
		CheckMouseEvent();
		DrawStats();
	}
	else if(level==4)
	{
		FsPollDevice();
		double d1=233.0/255.0,d2=214.0/255.0,d3=203.0/255.0;
		glClearColor(d1,d2,d3,1.0f);
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		//Letters
		glColor3ub(185,122,87);
		int i;
		char str[10];
		glRasterPos2d(200,150);
		YsGlDrawFontBitmap16x20("CAD Homework Score Board");
		glRasterPos2d(275,200);
		YsGlDrawFontBitmap16x20("Level 1");
		glRasterPos2d(275,240);
		YsGlDrawFontBitmap16x20("Level 2");
		glRasterPos2d(275,280);
		YsGlDrawFontBitmap16x20("Level 3");
		glRasterPos2d(275,320);
		YsGlDrawFontBitmap16x20("Total");

		glRasterPos2d(470,200);
		i=WinInfo[4*1-4];
		itoa(i,str,10);
		YsGlDrawFontBitmap16x20(str);
		glRasterPos2d(470,240);
		i=WinInfo[4*2-4];
		itoa(i,str,10);
		YsGlDrawFontBitmap16x20(str);
		glRasterPos2d(470,280);
		i=WinInfo[4*3-4];
		itoa(i,str,10);
		YsGlDrawFontBitmap16x20(str);
				
		glRasterPos2d(470,320);
		i=(WinInfo[4*1-4]+WinInfo[4*2-4]+WinInfo[4*3-4])*0.33;
		itoa(i,str,10);
		YsGlDrawFontBitmap16x20(str);
		
		if(i>=60)
		{
			glRasterPos2d(90,375);
			YsGlDrawFontBitmap16x20("Congradulations! You passed the game!");
		}
		else
		{
			glRasterPos2d(55,375);
			YsGlDrawFontBitmap16x20("Sorry, you didn't pass the game. Try again!");
		}
		
		glBegin(GL_QUADS);
		glVertex2i(250,425);
		glVertex2i(550,425);
		glVertex2i(550,500);
		glVertex2i(250,500);
		glEnd();

		glColor3ub(233,214,203);
		glRasterPos2d(325,475);
		YsGlDrawFontBitmap16x20("Exit Game");

		MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
		if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
	&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>250 && mx<550
		&& my>425 && my<500)
		{
			level=0;
			terminate==1;
			if (i>=60)
				return 1;
			else
				return 0;
		}
	}
	FsSwapBuffers();
	FsSleep(20);
}
	CleanUp();
	return 0;
}
int CADCLASS::ReadBackground()
{

	if(	   YSOK==PenPng.Decode("pen.png")
		&& YSOK==EraserPng.Decode("eraser.png")
		&& YSOK==CheckPng.Decode("check.png")
		&& YSOK==BackgroundPng[0].Decode("Q1-question.png")
		&& YSOK==AnswerPng[0].Decode("Q1-answer.png")

		&& YSOK==BackgroundPng[1].Decode("Q2-question.png")
		&& YSOK==AnswerPng[1].Decode("Q2-answer.png")
		
		&& YSOK==BackgroundPng[2].Decode("Q3-question.png")
		&& YSOK==AnswerPng[2].Decode("Q3-answer.png"))
	{
		printf("Png Files Load Success.\n");
		PenPng.Flip();
		EraserPng.Flip();
		CheckPng.Flip();
		BackgroundPng[0].Flip();
		AnswerPng[0].Flip();

		BackgroundPng[1].Flip();
		AnswerPng[1].Flip();
		
		BackgroundPng[2].Flip();
		AnswerPng[2].Flip();
		//Set transparency:
		for(int i=0;i<45;i++)
			for(int j=0;j<45;j++)
			{
				if(PenPng.rgba[4*(i+45*j)+0]==255 && PenPng.rgba[4*(i+45*j)+1]==0 
					&& PenPng.rgba[4*(i+45*j)+2]==255)
				PenPng.rgba[4*(i+45*j)+3] = 0;
				else
				PenPng.rgba[4*(i+45*j)+3] = 255;
			}
		for(int i=0;i<45;i++)
			for(int j=0;j<45;j++)
			{
				if(EraserPng.rgba[4*(i+45*j)+0]==255 && EraserPng.rgba[4*(i+45*j)+1]==0 
					&& EraserPng.rgba[4*(i+45*j)+2]==255)
				EraserPng.rgba[4*(i+45*j)+3] = 0;
				else
				EraserPng.rgba[4*(i+45*j)+3] = 255;
			}
		for(int i=0;i<45;i++)
			for(int j=0;j<45;j++)
			{
				if(CheckPng.rgba[4*(i+45*j)+0]==255 && CheckPng.rgba[4*(i+45*j)+1]==0 
					&& CheckPng.rgba[4*(i+45*j)+2]==255)
				CheckPng.rgba[4*(i+45*j)+3] = 0;
				else
				CheckPng.rgba[4*(i+45*j)+3] = 255;
			}
		return 1;
	}

	return 0;
}
void CADCLASS::DrawBackground()
{
    int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
	glRasterPos2d(0.0,(double)(BackgroundPng[level-1].hei-1));
	glDrawPixels(BackgroundPng[level-1].wid,BackgroundPng[level-1].hei,GL_RGBA,GL_UNSIGNED_BYTE,BackgroundPng[level-1].rgba);

	glEnable(GL_BLEND);    
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2d(730.0,530.0+(double)(PenPng.hei-1));
	glDrawPixels(PenPng.wid,PenPng.hei,GL_RGBA,GL_UNSIGNED_BYTE,PenPng.rgba);
	glRasterPos2d(655.0,530.0+(double)(EraserPng.hei-1));
	glDrawPixels(EraserPng.wid,EraserPng.hei,GL_RGBA,GL_UNSIGNED_BYTE,EraserPng.rgba);
	glRasterPos2d(580.0,530.0+(double)(EraserPng.hei-1));
	glDrawPixels(EraserPng.wid,EraserPng.hei,GL_RGBA,GL_UNSIGNED_BYTE,CheckPng.rgba);
    glDisable(GL_BLEND);

/*	Pen X:(730,775)   Pen Y:(530,575)
	Era X:(655,700)   Era Y:(530,575)
	Che X:(580,625)   Che Y:(530,575)
*/
}
int CADCLASS::CheckWinLevel()
{
	int range=20;
	if(level==1)
	{
		Lines check[3][2];
		int hit[3]={0,0,0},extra=0;

		check[0][0].x=185;		check[0][0].y=334;
		check[0][1].x=147;		check[0][1].y=399;

		check[1][0].x=185;		check[1][0].y=462;
		check[1][1].x=147;		check[1][1].y=399;

		check[2][0].x=185;		check[2][0].y=397;
		check[2][1].x=147;		check[2][1].y=399;
		
		ptr=head[idx];  		
		for(int i=0;i<n[idx]-1;i+=2)
		{
			int x1=ptr->lines.x;
			int y1=ptr->lines.y;
			ptr=ptr->next;
			int x2=ptr->lines.x;
			int y2=ptr->lines.y;
			if( x1<x2
				||(x1==x2 && y1<y2))
			{
				//Swap two points of the same line
				int xx,yy;
				xx=x1; yy=y1;
				x1=x2; y1=y2;
				x2=xx; y2=yy;
			}

			if(abs(check[0][0].x-x1)-range<0
				&& abs(check[0][0].y-y1)-range<0
				&& abs(check[0][1].x-x2)-range<0
				&& abs(check[0][1].y-y2)-range<0)
				{
					hit[0]=1;
					ptr=ptr->next;
				}
			else if(abs(check[1][0].x-x1)-range<0
				&& abs(check[1][0].y-y1)-range<0
				&& abs(check[1][1].x-x2)-range<0
				&& abs(check[1][1].y-y2)-range<0)
				{
					hit[1]=1;
					ptr=ptr->next;
				}
			else if(abs(check[2][0].x-x1)-range<0
				&& abs(check[2][0].y-y1)-range<0
				&& abs(check[2][1].x-x2)-range<0
				&& abs(check[2][1].y-y2)-range<0)
				{
					hit[2]=1;
					ptr=ptr->next;
				}
			else {
				extra=1;
				ptr=ptr->next;
			}
		}
		WinInfo[1]=hit[0]+hit[1]+hit[2];
		WinInfo[2]=3;  // [0] out of 3 is correct.
		WinInfo[3]=extra; //If there's redundent lines.
		WinInfo[0]=100*((double)WinInfo[1])/((double)WinInfo[2])-10*WinInfo[3];
		if(WinInfo[0]<0)
			WinInfo[0]=0;
		return 1;
	}
	else if(level==2)
	{
		Lines check[6][2];
		int hit[6]={0,0,0,0,0,0},extra=0;

		check[0][0].x=170;		check[0][0].y=198;
		check[0][1].x=170;		check[0][1].y=98;

		check[1][0].x=223;		check[1][0].y=198;
		check[1][1].x=120;		check[1][1].y=198;

		check[2][0].x=120;		check[2][0].y=220;
		check[2][1].x=120;		check[2][1].y=198;
		
		check[3][0].x=120;		check[3][0].y=220;
		check[3][1].x=88;		check[3][1].y=220;
		
		check[4][0].x=223;		check[4][0].y=220;
		check[4][1].x=223;		check[4][1].y=198;
		
		check[5][0].x=253;		check[5][0].y=220;
		check[5][1].x=223;		check[5][1].y=220;

		ptr=head[idx];  		
		for(int i=0;i<n[idx]-1;i+=2)
		{
			int x1=ptr->lines.x;
			int y1=ptr->lines.y;
			ptr=ptr->next;
			int x2=ptr->lines.x;
			int y2=ptr->lines.y;
			if( x1<x2
				||(x1==x2 && y1<y2))
			{
				int xx,yy;
				xx=x1; yy=y1;
				x1=x2; y1=y2;
				x2=xx; y2=yy;
			}
			if(abs(check[0][0].x-x1)-range<0
				&& abs(check[0][0].y-y1)-range<0
				&& abs(check[0][1].x-x2)-range<0
				&& abs(check[0][1].y-y2)-range<0)
				{
					hit[0]=1;
					ptr=ptr->next;
				}
			else if(abs(check[1][0].x-x1)-range<0
				&& abs(check[1][0].y-y1)-range<0
				&& abs(check[1][1].x-x2)-range<0
				&& abs(check[1][1].y-y2)-range<0)
				{
					hit[1]=1;
					ptr=ptr->next;
				}
			else if(abs(check[2][0].x-x1)-range<0
				&& abs(check[2][0].y-y1)-range<0
				&& abs(check[2][1].x-x2)-range<0
				&& abs(check[2][1].y-y2)-range<0)
				{
					hit[2]=1;
					ptr=ptr->next;
				}
			else if(abs(check[3][0].x-x1)-range<0
				&& abs(check[3][0].y-y1)-range<0
				&& abs(check[3][1].x-x2)-range<0
				&& abs(check[3][1].y-y2)-range<0)
				{
					hit[3]=1;
					ptr=ptr->next;
				}
			else if(abs(check[4][0].x-x1)-range<0
				&& abs(check[4][0].y-y1)-range<0
				&& abs(check[4][1].x-x2)-range<0
				&& abs(check[4][1].y-y2)-range<0)
				{
					hit[4]=1;
					ptr=ptr->next;
				}
			else if(abs(check[5][0].x-x1)-range<0
				&& abs(check[5][0].y-y1)-range<0
				&& abs(check[5][1].x-x2)-range<0
				&& abs(check[5][1].y-y2)-range<0)
				{
					hit[5]=1;
					ptr=ptr->next;
				}
			else {
				extra=1;
				ptr=ptr->next;
			}
		}
		WinInfo[5]=hit[0]+hit[1]+hit[2]+hit[3]+hit[4]+hit[5];
		WinInfo[6]=6;  // [0] out of 3 is correct.
		WinInfo[7]=extra; //If there's redundent lines.
		WinInfo[4]=100*((double)WinInfo[1])/((double)WinInfo[2])-10*WinInfo[3];
		if(WinInfo[4]<0)
			WinInfo[4]=0;
		return 1;
	}
	else if(level==3)
	{
		Lines check[4][2];
		int hit[4]={0,0,0,0},extra=0;

		check[0][0].x=177;		check[0][0].y=463;
		check[0][1].x=177;		check[0][1].y=416;

		check[1][0].x=518;		check[1][0].y=229;
		check[1][1].x=518;		check[1][1].y=154;

		check[2][0].x=565;		check[2][0].y=154;
		check[2][1].x=518;		check[2][1].y=154;
		
		check[3][0].x=565;		check[3][0].y=229;
		check[3][1].x=565;		check[3][1].y=154;
		
		ptr=head[idx];  		
		for(int i=0;i<n[idx]-1;i+=2)
		{
			int x1=ptr->lines.x;
			int y1=ptr->lines.y;
			ptr=ptr->next;
			int x2=ptr->lines.x;
			int y2=ptr->lines.y;
			if( x1<x2
				||(x1==x2 && y1<y2))
			{
				int xx,yy;
				xx=x1; yy=y1;
				x1=x2; y1=y2;
				x2=xx; y2=yy;
			}
			if(abs(check[0][0].x-x1)-range<0
				&& abs(check[0][0].y-y1)-range<0
				&& abs(check[0][1].x-x2)-range<0
				&& abs(check[0][1].y-y2)-range<0)
				{
					hit[0]=1;
					ptr=ptr->next;
				}
			else if(abs(check[1][0].x-x1)-range<0
				&& abs(check[1][0].y-y1)-range<0
				&& abs(check[1][1].x-x2)-range<0
				&& abs(check[1][1].y-y2)-range<0)
				{
					hit[1]=1;
					ptr=ptr->next;
				}
			else if(abs(check[2][0].x-x1)-range<0
				&& abs(check[2][0].y-y1)-range<0
				&& abs(check[2][1].x-x2)-range<0
				&& abs(check[2][1].y-y2)-range<0)
				{
					hit[2]=1;
					ptr=ptr->next;
				}
			else if(abs(check[3][0].x-x1)-range<0
				&& abs(check[3][0].y-y1)-range<0
				&& abs(check[3][1].x-x2)-range<0
				&& abs(check[3][1].y-y2)-range<0)
				{
					hit[3]=1;
					ptr=ptr->next;
				}
			else {
				extra=1;
				ptr=ptr->next;
			}
		}
		WinInfo[9]=hit[0]+hit[1]+hit[2]+hit[3];
		WinInfo[10]=4;  // [0] out of 3 is correct.
		WinInfo[11]=extra; //If there's redundent lines.
		WinInfo[8]=100*((double)WinInfo[9])/((double)WinInfo[10])-10*WinInfo[11];
		if(WinInfo[8]<0)
			WinInfo[8]=0;
		return 1;
	}
	return 0;
}
void CADCLASS::CheckMouseEvent()
{
	MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
	//Hit Erase Button:
	if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
	&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>730 && mx<775
		&& my>530 && my<575
		&& ConfirmationWindow==Uncalled)
	{
		LineState=Draw;
		MouseClick=1;
	}
	//Hit Erase Button:
	else if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
	&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>655 && mx<700
		&& my>530 && my<575
		&& ConfirmationWindow==Uncalled)
	{
		PreventLeak();
		LineState=Erase;
	}
	//Hit Check Button:
	else if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>580 && mx<625
		&& my>530 && my<575
		&& ConfirmationWindow==Uncalled)
	{
		ConfirmationWindow=Calling;
		PreventLeak();
		LineState=ShowWinStats;
		MouseClick=1;
	}

	if((mx<580 || (mx>625&&mx<730) || mx>775)
	|| (my<530 || my>575))
		MouseClick=0;
	
	if(LineState==Draw && MouseClick==0)
		AddLines();
	else if(LineState==Erase)
		EraseLines();

}
void CADCLASS::DrawStats()
{
	if(LineState==ShowWinStats && ConfirmationWindow==Calling)
	{
		//Dark Brwon Frame
		glColor3ub(185,122,87);
		glBegin(GL_QUADS);
		glVertex2i(250,225);
		glVertex2i(550,225);
		glVertex2i(550,375);
		glVertex2i(250,375);
		glEnd();
		//Light Brown Background
		glColor3ub(233,214,203);
		glBegin(GL_QUADS);
		glVertex2i(252,227);
		glVertex2i(548,227);
		glVertex2i(548,373);
		glVertex2i(252,373);
		glEnd();
		//Yes Button Dark Brown Fram
		glColor3ub(185,122,87);
		glBegin(GL_QUADS);
		glVertex2i(290,315);
		glVertex2i(370,315);
		glVertex2i(370,350);
		glVertex2i(290,350);
		glEnd();
		//Yes Button Light Brown Background
		glColor3ub(233,214,203);
		glBegin(GL_QUADS);
		glVertex2i(292,317);
		glVertex2i(368,317);
		glVertex2i(368,348);
		glVertex2i(292,348);
		glEnd();
		//Letters
		glColor3ub(185,122,87);
		glRasterPos2d(305,344);
		YsGlDrawFontBitmap16x20("YES");
		//No Button Dark Brown Fram
		glColor3ub(185,122,87);
		glBegin(GL_QUADS);
		glVertex2i(430,315);
		glVertex2i(510,315);
		glVertex2i(510,350);
		glVertex2i(430,350);
		glEnd();
		//No Button Light Brown Background
		glColor3ub(233,214,203);
		glBegin(GL_QUADS);
		glVertex2i(432,317);
		glVertex2i(508,317);
		glVertex2i(508,348);
		glVertex2i(432,348);
		glEnd();
		//Letters
		glColor3ub(185,122,87);
		glRasterPos2d(454,344);
		YsGlDrawFontBitmap16x20("NO");
		glRasterPos2d(275,270);
		YsGlDrawFontBitmap16x20("ARE YOU SURE YOU");
		glRasterPos2d(280,300);
		YsGlDrawFontBitmap16x20("WANT TO SUBMIT?");
		if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>290 && mx<370
		&& my>315 && my<350)
		{
			if(1==CheckWinLevel())
				ConfirmationWindow=Proceed;
		}
		else if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>430 && mx<510
		&& my>315 && my<350)
		{
			ConfirmationWindow=Uncalled;
		}
	}
	else if(LineState==ShowWinStats 
		&& ConfirmationWindow==Proceed)
	{
		//Dark Brwon Frame
		glColor3ub(185,122,87);
		glBegin(GL_QUADS);
		glVertex2i(150,150);
		glVertex2i(150,450);
		glVertex2i(650,450);
		glVertex2i(650,150);
		glEnd();
		//Light Brown Background
		glColor3ub(233,214,203);
		glBegin(GL_QUADS);
		glVertex2i(152,152);
		glVertex2i(152,448);
		glVertex2i(648,448);
		glVertex2i(648,152);
		glEnd();
		//Letters
		glColor3ub(185,122,87);
		int i;
		char str[10];
		glRasterPos2d(190,200);
		if(level==1)
			YsGlDrawFontBitmap16x20("Your score for level 1 is:");
		else if(level==2)
			YsGlDrawFontBitmap16x20("Your score for level 2 is:");
		else if(level==3)
			YsGlDrawFontBitmap16x20("Your score for level 3 is:");
		glRasterPos2d(200,230);
		i=WinInfo[4*level-4];
		itoa(i,str,10);
		YsGlDrawFontBitmap16x20(str);
		glRasterPos2d(200,260);
		YsGlDrawFontBitmap16x20("=    out of   lines");	
		i=WinInfo[4*level-3];
		itoa(i,str,10);
		glRasterPos2d(240,260);
		YsGlDrawFontBitmap16x20(str);
		i=WinInfo[4*level-2];
		itoa(i,str,10);
		glRasterPos2d(400,260);
		YsGlDrawFontBitmap16x20(str);
		if(WinInfo[4*level-1])
		{
			glRasterPos2d(200,290);
			YsGlDrawFontBitmap16x20(" -10 for wrong lines");
		}
		//Dark Brwon Frame
		glColor3ub(185,122,87);
		glBegin(GL_QUADS);
		glVertex2i(200,350);
		glVertex2i(200,425);
		glVertex2i(350,425);
		glVertex2i(350,350);
		glEnd();
		//Light Brown Background
		glColor3ub(233,214,203);
		glBegin(GL_QUADS);
		glVertex2i(202,352);
		glVertex2i(202,423);
		glVertex2i(348,423);
		glVertex2i(348,352);
		glEnd();
		//Letters
		glColor3ub(185,122,87);
		glRasterPos2d(223,385);
		YsGlDrawFontBitmap16x20("Correct");
		glRasterPos2d(228,410);
		YsGlDrawFontBitmap16x20("Answer");
		//Dark Brwon Frame
		glColor3ub(185,122,87);
		glBegin(GL_QUADS);
		glVertex2i(450,350);
		glVertex2i(450,425);
		glVertex2i(600,425);
		glVertex2i(600,350);
		glEnd();
		//Light Brown Background
		glColor3ub(233,214,203);
		glBegin(GL_QUADS);
		glVertex2i(452,352);
		glVertex2i(452,423);
		glVertex2i(598,423);
		glVertex2i(598,352);
		glEnd();
		//Letters
		if(level!=3)
		{
			glColor3ub(185,122,87);
			glRasterPos2d(500,385);
			YsGlDrawFontBitmap16x20("Next");
			glRasterPos2d(490,410);
			YsGlDrawFontBitmap16x20("Level");
		}
		else if(level==3)
		{
			glColor3ub(185,122,87);
			glRasterPos2d(490,385);
			YsGlDrawFontBitmap16x20("Total");
			glRasterPos2d(490,410);
			YsGlDrawFontBitmap16x20("Score");
		}
		if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>200 && mx<350
		&& my>350 && my<425)
		{
			ShowAnswer=1;
		}
		if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent
		&& mx>450 && mx<600
		&& my>350 && my<425)
		{
			level++;
			ConfirmationWindow=Uncalled;
			LineState=Draw;
			idx++;
			/*int temp=ReadBackground();
			if(0==temp)
			{
				printf("Question File Load Error.\n");
			}*/
		}
	}
}
void CADCLASS::DrawLines()
{
	DoublyLinkedListItem <Lines> *ptr;
	if(n[idx]%2==1 && n[idx]!=0 && tail[idx]!=NULL && head[idx]!=NULL)
	{
		glColor3ub(0,0,0);
		ptr=head[idx];  		
		for(int i=0;i<n[idx]-1 && NULL!=ptr;i+=2)
		{
			glBegin(GL_LINES);
			glVertex2i(ptr->lines.x,ptr->lines.y);
			ptr=ptr->next;
			glVertex2i(ptr->lines.x,ptr->lines.y);
			ptr=ptr->next;
			glEnd();
		}
		glBegin(GL_LINES);	
		glVertex2i(tail[idx]->lines.x,tail[idx]->lines.y);
		glVertex2i(mx,my);
		glEnd();
		
	}
	else if(n[idx]%2==0 && n[idx]!=0 && tail[idx]!=NULL)
	{
		ptr=head[idx];
		glColor3ub(0,0,0);
		for(int i=0;i<n[idx]-1 && NULL!=ptr;i+=2)
		{
			glBegin(GL_LINES);
			glVertex2i(ptr->lines.x,ptr->lines.y);
			ptr=ptr->next;
			glVertex2i(ptr->lines.x,ptr->lines.y);
			ptr=ptr->next;
			glEnd();
		}
	}
}
void CADCLASS::AddLines()
{
	if(FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent 
		&& lb==1 && mx>0 && mx<800
		&& my>0 && my<600 && level!=0)
	{
		newline=new DoublyLinkedListItem<Lines>;
		newline->lines.x=mx;
		newline->lines.y=my;
		n[idx]++;
		if(NULL==tail[idx] || head[idx]==NULL)
		{
			head[idx]=newline;
			tail[idx]=newline;
			head[idx]->next=NULL;
			head[idx]->prev=NULL;
			tail[idx]->next=NULL;
			tail[idx]->prev=NULL;
		}
		else
		{
			tail[idx]->next=newline;
			newline->prev=tail[idx];
			tail[idx]=newline;
			tail[idx]->next=NULL;
		}
	}


}
void CADCLASS::EraseLines()
{
	//Draw Eraser Circle
	double rad=25;
	double PI=3.1415926535;
	glColor3ub(255,0,0);
	glBegin(GL_LINE_LOOP);
	for(int j=0; j<64; j++)
	{
		double angle=(double)j*PI/32.0;
		double x=mx+cos(angle)*rad;
		double y=my+sin(angle)*rad;
		glVertex2d(x,y);

	}
	glEnd();
	//Check and Delete
	ptr=head[idx];  		
	for(int i=0;i<n[idx]-1 && NULL!=ptr;i+=2)
	{
		double x1=(double)ptr->lines.x;
		double y1=(double)ptr->lines.y;
		ptr=ptr->next;
		double x2=(double)ptr->lines.x;
		double y2=(double)ptr->lines.y;
		double dis=CalculateDistance(x1,y1,x2,y2);
		if(dis<rad
		&& FSMOUSEEVENT_LBUTTONUP!=MouseEvent
		&& FSMOUSEEVENT_LBUTTONDOWN==MouseEvent 
		&& lb==1)
		{
			n[idx]-=2;
			DeleteLineMember();
		}
		else ptr=ptr->next;
	}	
}
double CADCLASS::CalculateDistance(double x1,double y1,double x2,double y2)
{
	double ax=x2-x1,ay=y2-y1,bx=mx-x1,by=my-y1,cx=x2-mx,cy=y2-my;
	double aNorm=sqrt(ax*ax+ay*ay);
	double bNorm=sqrt(bx*bx+by*by);
	double cNorm=sqrt(cx*cx+cy*cy);
	double abCrossProduct=abs(bx*ay-ax*by);
	double dis=abCrossProduct/aNorm;
	double cosab=(ax*bx+ay*by)/(aNorm*bNorm);
	double cosbc=(bx*cx+by*cy)/(bNorm*cNorm);
	if(cosab>0 && cosbc>0)
		return dis;
	else if(bNorm<cNorm)
		return bNorm;
	else if(cNorm<bNorm)
		return cNorm;
}
void CADCLASS::PreventLeak()
{
	if(n[idx]%2==1 && tail[idx]!=NULL)
	{
		if(tail[idx]->prev!=NULL)
		{
			tail[idx]=tail[idx]->prev;
			tail[idx]->next=NULL;
			n[idx]--;
		}
		else 
		{
			head[idx]=NULL;
			tail[idx]=NULL;
			n[idx]=0;
		}
	}
}
void CADCLASS::DeleteLineMember()
{
	if(ptr->next==NULL 
		&& ptr->prev->prev==NULL)
	{
		head[idx]=NULL;
		tail[idx]=NULL;
		tail[idx]->prev=NULL;
		ptr=NULL;
	}
	else if(ptr->next!=NULL 
		&& ptr->prev->prev==NULL)
	{
		ptr=ptr->next;
		ptr->prev=NULL;
		head[idx]=ptr;
	}			
	else if(ptr->next==NULL 
		&& ptr->prev->prev!=NULL)
	{
		tail[idx]=ptr->prev->prev;
		tail[idx]->next=NULL;
		ptr=NULL;
	}
	else if(ptr->next!=NULL)
	{
		ptr->next->prev=ptr->prev->prev;
		ptr->prev->prev->next=ptr->next;
		ptr=ptr->next;
	}
}