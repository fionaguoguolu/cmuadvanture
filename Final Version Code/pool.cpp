#include "pool.h"

PoolGame :: PoolGame()
{
	gamestate=1;
	score=0;
	playtime=0;
	cueHit=0;
	timelimit=120;
	state=0;
	BallsHit=0;
	for(int i=0;i<16;i++)
		for(int j=0;j<2;j++)
			{
				BallVel[i]=0.0;
				//BallPos[i][1]=200;
				dirVector[i][j]=0;
				radius[i]=0.0;
				mass[i]=1.0;
			}
		
	BallPos[0][0]=125;
	BallPos[0][1]=225;
	BallPos[1][0]=650;
	BallPos[1][1]=177;
	BallPos[2][0]=650;
	BallPos[2][1]=201;
	BallPos[3][0]=650;
	BallPos[3][1]=225;
	BallPos[4][0]=650;
	BallPos[4][1]=249;
	BallPos[5][0]=650;
	BallPos[5][1]=273;
	BallPos[6][0]=629;
	BallPos[6][1]=189;
	BallPos[7][0]=629;
	BallPos[7][1]=213;
	BallPos[8][0]=629;
	BallPos[8][1]=237;
	BallPos[9][0]=629;
	BallPos[9][1]=261;
	BallPos[10][0]=608;
	BallPos[10][1]=201;
	BallPos[11][0]=608;
	BallPos[11][1]=225;
	BallPos[12][0]=608;
	BallPos[12][1]=249;
	BallPos[13][0]=587;
	BallPos[13][1]=213;
	BallPos[14][0]=587;
	BallPos[14][1]=237;
	BallPos[15][0]=566;
	BallPos[15][1]=225;
}

void PoolGame :: ExitGame(int win)
{
	YsRawPngDecoder png1;
	glColor3f(0.0,0.0,0.0);
	int key,esc=1;
	while(esc)
	{
		if(win==1)
			{
				FsPollDevice();
				key=FsInkey();
				if(key==FSKEY_ESC)
					esc=0;
				int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glViewport(0,0,winWid,winHei);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
				glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
				
				if(YSOK==png1.Decode("win.png"))
				png1.Flip();

				glRasterPos2d(0.0,(double)(png1.hei-1));
				glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
				FsSwapBuffers();
				FsSleep(50);
				/*
				glRasterPos2d(330,230);
				YsGlDrawFontBitmap20x32("YOU WIN!");
				FsSwapBuffers();
				FsSleep(50);*/

			}
		if(win==0)
			{
				FsPollDevice();
				key=FsInkey();
				if(key==FSKEY_ESC)
					esc=0;
				int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glViewport(0,0,winWid,winHei);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
				glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

				if(YSOK==png1.Decode("lose.png"))
				png1.Flip();

				glRasterPos2d(0.0,(double)(png1.hei-1));
				glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
				FsSwapBuffers();
				FsSleep(50);
				/*FsPollDevice();
				key=FsInkey();
				if(key==FSKEY_ESC)
					esc=0;
				glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
				glRasterPos2d(330,230);
				YsGlDrawFontBitmap20x32("YOU LOSE!");
				FsSwapBuffers();
				FsSleep(50);*/
			}
		
		
	}
	gamestate=1;
	score=0;
	playtime=0;
	cueHit=0;
	timelimit=120;
	state=0;
	BallsHit=0;
	for(int i=0;i<16;i++)
		for(int j=0;j<2;j++)
			{
				BallVel[i]=0.0;
				//BallPos[i][1]=200;
				dirVector[i][j]=0;
				radius[i]=0.0;
				mass[i]=1.0;
			}
		
	BallPos[0][0]=125;
	BallPos[0][1]=225;
	BallPos[1][0]=650;
	BallPos[1][1]=177;
	BallPos[2][0]=650;
	BallPos[2][1]=201;
	BallPos[3][0]=650;
	BallPos[3][1]=225;
	BallPos[4][0]=650;
	BallPos[4][1]=249;
	BallPos[5][0]=650;
	BallPos[5][1]=273;
	BallPos[6][0]=629;
	BallPos[6][1]=189;
	BallPos[7][0]=629;
	BallPos[7][1]=213;
	BallPos[8][0]=629;
	BallPos[8][1]=237;
	BallPos[9][0]=629;
	BallPos[9][1]=261;
	BallPos[10][0]=608;
	BallPos[10][1]=201;
	BallPos[11][0]=608;
	BallPos[11][1]=225;
	BallPos[12][0]=608;
	BallPos[12][1]=249;
	BallPos[13][0]=587;
	BallPos[13][1]=213;
	BallPos[14][0]=587;
	BallPos[14][1]=237;
	BallPos[15][0]=566;
	BallPos[15][1]=225;
}

void PoolGame :: DrawTable() const
{

	glColor3f(0.753,0.314,0.302);
	glBegin(GL_QUADS);

	glVertex2d(0,0);
	glVertex2d(800,0);
	glVertex2d(900,500);
	glVertex2d(0,500);
	glEnd();

	glColor3d(0.482,0.647,0.690);
	glBegin(GL_QUADS);

	glVertex2d(50,40);
	glVertex2d(750,40);
	glVertex2d(750,460);
	glVertex2d(50,460);
	glEnd();

	glColor3f(0.0,0.0,0.0);
	DrawCircle(55,45,30);
	DrawCircle(400,45,30);
	DrawCircle(745,45,30);
	DrawCircle(55,455,30);
	DrawCircle(400,455,30);
	DrawCircle(745,455,30);




	/*
	if(YSOK==png.Decode("pt.png"))
		png.Flip();

	glRasterPos2d(0.0,(double)(png.hei-1));
	glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba); */
}


void PoolGame :: DrawBalls() const
{
	const double YS_PI=3.1415927;
	double rad=11;
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	for(int i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32.0;
        double x=(double)BallPos[0][0]+cos(angle)*(double)rad;
        double y=(double)BallPos[0][1]+sin(angle)*(double)rad;
        glVertex2d(x,y);
    }
	glEnd();

	glColor3f(1.0,0.0,0.0);
	//glBegin(GL_POLYGON);
	
	for(int n=1;n<16;n++)
	{
		DrawCircle(BallPos[n][0],BallPos[n][1],11);
	}
	//glEnd();

}

void PoolGame :: DrawCircle(int cx,int cy,int rad) const
{
    const double YS_PI=3.1415927;

   // glColor3f(1.0,0.0,0.0);
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

void PoolGame :: DrawPowerBar(int power)
{
	glColor3f(0.0,0.0,1.0);
	
	glRasterPos2d(70,560);
    YsGlDrawFontBitmap16x20("Power");
	
	glBegin(GL_QUADS);

	glVertex2i(165,530);
	glVertex2i(165+power/15,530);
	glVertex2i(165+power/15,565);
	glVertex2i(165,565);
	glEnd();
		
}

float PoolGame :: magnitude(float x,float y) const
{
	return sqrt(x*x+y*y);
}

void PoolGame :: DrawCue(int x,int y) const
{
	int cx=BallPos[0][0],cy=BallPos[0][1];
	x=x-cx;y=cy-y;
	int rx=-x,ry=-y;
	
	
	float vecMag=magnitude((float)rx,(float)ry);
	int x1=(int)((14/vecMag)*rx),x2=(int)((225/vecMag)*rx),y1=(int)((14/vecMag)*ry),y2=(int)((225/vecMag)*ry);
	x1=cx+x1;x2=cx+x2;
	y1=cy-y1;y2=cy-y2;

	glLineWidth(3.0);
	glColor3f(0.937,0.894,0.630);
	
	glBegin(GL_LINES);
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	
	glEnd();

}

void PoolGame :: DrawTime(int time)
{
	char sec[50];
	int dt=timelimit-time;
	if(dt<0)
		dt=0;
	sprintf(sec,"Time left: %d seconds",dt);
	glColor3f(0.0,0.0,1.0);
	
	glRasterPos2d(70,590);
    YsGlDrawFontBitmap16x20(sec);
}

void PoolGame :: CalcCueHit(int x,int y,float pow)
{
	int cx=BallPos[0][0],cy=BallPos[0][1];
	x=x-cx;
	y=-(cy-y);
	float mag=magnitude((float)x,(float)y);
	dirVector[0][0]=((float)x/mag);
	dirVector[0][1]=((float)y/mag);
	BallVel[0]= (pow/1500)*1100 + 100.0;
	
	
}

void PoolGame :: MoveBalls()
{
	time_t now;
	for(int i=0;i<16;i++)
	{
		
		time(&now);
		BallPos[i][0]	= BallPos[i][0]		+	0.01*dirVector[i][0]*BallVel[i];
		BallPos[i][1]	= BallPos[i][1]		+	0.01*dirVector[i][1]*BallVel[i];
		BallVel[i]		= BallVel[i]		-	0.01*300;
		if(BallVel[i]<1)
		{
			BallVel[i]=0;
		}
		//printf("%f\n",BallVel[0]);
	}

}

void PoolGame :: CollisionCheck()
{
	
	int i,j;
    for(i=0; i<16; i++)
    {
        for(j=i+1; j<16; j++)
        {
            AfterCollision(BallPos[i][0],BallPos[i][1],
							dirVector[i][0]*BallVel[i],dirVector[i][1]*BallVel[i],BallPos[j][0],
							BallPos[j][1],dirVector[j][0]*BallVel[j],dirVector[j][1]*BallVel[j],12.0,i,j);
        }
    }
	
}

void PoolGame :: AfterCollision(float x1, float y1,float vx1,float vy1,float x2,float y2,float vx2,float vy2,float rad,
								int b1, int b2)
{
	 double dx=x2-x1,dy=y2-y1;
    double d=dx*dx+dy*dy;
    if(d<(rad*2.0)*(rad*2.0))
    {
        double nx,ny,nl;
        nx=x2-x1;
        ny=y2-y1;

        nl=nx*nx+ny*ny;
        if(0.0<nl)
        {
            nl=sqrt(nl);
            nx/=nl+0.01;
            ny/=nl+0.01;

            double nv1,nv2;
            nv1=(vx1*nx+vy1*ny);
            nv2=(vx2*nx+vy2*ny);

            if((nv2>=0.0 && nv2<nv1) || (nv1<=0.0 && nv2<nv1) || (nv1>=0.0 && nv2<=0.0)) // Means closing in.  Otherwise, two molecules are moving away.
            {
                vx1=vx1-nx*nv1+nx*nv2;
				vy1=vy1-ny*nv1+ny*nv2;
				vx2=vx2-nx*nv2+nx*nv1;
				vy2=vy2-ny*nv2+ny*nv1;
				float vm1=magnitude(vx1,vy1),vm2=magnitude(vx2,vy2);
				dirVector[b1][0]=vx1/(vm1+0.01);
				dirVector[b1][1]=vy1/(vm1+0.01);
				dirVector[b2][0]=vx2/(vm2+0.01);
				dirVector[b2][1]=vy2/(vm2+0.01);
				BallVel[b1]=vm1;
				BallVel[b2]=vm2;
            }
        }
    }
}

void PoolGame :: bounce()
{
	for(int i=0;i<16;i++)
	{
		if( (BallPos[i][1]<52 && BallPos[i][0]>77 && BallPos[i][0] < 373 && dirVector[i][1]<0) ||
			(BallPos[i][1]<52 && BallPos[i][0]>427 && BallPos[i][0] < 723 && dirVector[i][1]<0)  )
		{
			dirVector[i][1]=-dirVector[i][1];
			BallVel[i]=0.9*BallVel[i];
		}

		if( (BallPos[i][1]>448 && BallPos[i][0]>77 && BallPos[i][0] < 373 && dirVector[i][1]>0) ||
			(BallPos[i][1]>448 && BallPos[i][0]>427 && BallPos[i][0] < 723 && dirVector[i][1]>0)  )
		{
			dirVector[i][1]=-dirVector[i][1];
			BallVel[i]=0.9*BallVel[i];
		}

		if( (BallPos[i][0]<62 && BallPos[i][1]>72 && BallPos[i][1]<422 && dirVector[i][0]<0))
		{
			dirVector[i][0]=-dirVector[i][0];
			BallVel[i]=0.9*BallVel[i];
		}

		if( (BallPos[i][0]>738 && BallPos[i][1]>72 && BallPos[i][1]<422 && dirVector[i][0]>0))
		{
			dirVector[i][0]=-dirVector[i][0];
			BallVel[i]=0.9*BallVel[i];
		}
	}
}

int PoolGame :: Ballstop()
{
	int stop=1;
	for(int i=0;i<16;i++)
	{
		if(BallVel[i]!=0)
			stop=0;
	}
	return stop;
}

void PoolGame ::checkPocket()
{
	int pockets[6][2]={{55,45},{400,45},{745,45},
					{55,455},{400,455},{745,455}};
	for(int i=0;i<16;i++)
	{
		for(int p=0;p<6;p++)
		{
			if(distance(BallPos[i][0],BallPos[i][1],pockets[p][0],pockets[p][1])<30)
			{
				BallsHit++;
				BallPos[i][0]=280 + BallsHit*28;
				BallPos[i][1]=545;
				dirVector[i][0]=0;
				dirVector[i][1]=0;
				BallVel[i]=0;
				
				if(i==0)
				{
					cueHit=1;
					BallsHit--;
				}
			}
		}
	}
	
}

float PoolGame :: distance(int x1,int y1,int x2,int y2) const
{
	const float dist=sqrt((float)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
	return dist;
}

void PoolGame :: DrawIntroScreen() const
{
	DrawTable();
	glColor3f(1.0,1.0,1.0);
	
	glRasterPos2d(65,142);
    YsGlDrawFontBitmap12x16("Instructions:");

	
	glRasterPos2d(65,180);
	YsGlDrawFontBitmap12x16("1.Use the mouse pointer to control the Cue");

	glRasterPos2d(65,218);
	YsGlDrawFontBitmap12x16("2. Left click to hit");

	glRasterPos2d(65,256);
	YsGlDrawFontBitmap12x16("3. Press ESC to quit at any point of the game");

	glRasterPos2d(65,294);
	YsGlDrawFontBitmap12x16("4. Now, press ENTER to start the game");

	glRasterPos2d(65,332);
	YsGlDrawFontBitmap12x16("5. Finish the game (Pocket all balls) in t<2 mins to pass");
}
int PoolGame :: rungame()
{
	FsOpenWindow(25,25,800,600,1);
	time_t start;
	
	int power=0,mouseEvent,lb,mb,rb,mx,my,key,step=1,win=0;
	while(gamestate)
	{
		while(gamestate && state==0)
		{
			FsPollDevice();
			key=FsInkey();
			if(key==FSKEY_ESC)
				gamestate=0;
			if(key==FSKEY_ENTER)
				state=1;
			int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glViewport(0,0,winWid,winHei);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
			DrawIntroScreen();
			FsSwapBuffers();
			FsSleep(10);
			time(&start);
		}

		while(gamestate && state==1)
		{
			
			if(cueHit==1)
			{
				BallPos[0][0]=200;
				BallPos[0][1]=225;
				BallVel[0]=0;
				dirVector[0][0]=0;
				dirVector[0][1]=0;
				cueHit=0;
				timelimit-=10;
			}
			if(BallsHit==15)
				gamestate=0;
			FsPollDevice();
			key=FsInkey();
			if(key==FSKEY_ESC)
				gamestate=0;
			int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glViewport(0,0,winWid,winHei);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
			if(power>1500)
				step=-step;
			if(power<0)
				step=-step;
			power=power+20*step;
			DrawTable();
			DrawBalls();
			DrawPowerBar(power);
			mouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
			DrawCue(mx,my);
			DrawTime((int)(time(NULL)-start));
			FsSwapBuffers();
			FsSleep(10);
			
			if(time(NULL)-start>=timelimit)
				gamestate=0;
			if(mouseEvent==FSMOUSEEVENT_LBUTTONDOWN)
			{
				CalcCueHit(mx,my,power);
				state=2;
			}

		}

		while(gamestate==1 && state==2)
		{
			FsPollDevice();
			key=FsInkey();
			if(key==FSKEY_ESC)
				gamestate=0;
			
			bounce();
			checkPocket();
			CollisionCheck();
			MoveBalls();
			//printf("%f,%f\n",BallPos[0][0],BallPos[0][1]);
			int winWid,winHei;
			FsGetWindowSize(winWid,winHei);
			glViewport(0,0,winWid,winHei);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		
			DrawTable();
			DrawPowerBar(power);
			DrawBalls();
			DrawTime((int)(time(NULL)-start));
			FsSwapBuffers();
			FsSleep(10);
			if(Ballstop())
				state=1;
			if(BallsHit==15 && (time(NULL)-start)<timelimit)
			{
				gamestate=0;
				win=1;
				//printf("BallsHit");
			}
		}
	}
	ExitGame(win);
	return win;
}

