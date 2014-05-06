#include "Map.h"

void Map::ShowShrinkMap()
{
    YsRawPngDecoder png1;
    if(YSOK==png1.Decode("suisuipng-with light.png"))
    {
        png1.Flip();
        int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glRasterPos2d(0.0,(double)(winHei-1));
        glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        // changes by Chun Fan
		//printf("%d  %d",png1.wid,png1.hei);
    }

    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
    int i;
    int cx,cy,rad=8;
    
    cx=midpointx*939/2656+3;
    cy=600-midpointy*600/1694;
    
    for(i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32.0;
        double x=(double)cx+cos(angle)*(double)rad;
        double y=(double)cy+sin(angle)*(double)rad;
        glVertex2d(x,y);
    }
    
    glEnd();
}

void Map:: CheckPlayersState()
{
    if (key==FSKEY_LEFT || key==FSKEY_RIGHT || key==FSKEY_UP || key==FSKEY_DOWN)
    {
        keyStrikeTime++;
        player.KeySignalstate=1;
        player.PlayersState=keyStrikeTime%10;// depends on how many gif compenents we have
    }
    else
    {
        player.KeySignalstate=0;
        player.PlayersState=keyStrikeTime%10;
    }
    
}

int Map::GetPlayersPositionX()
{
    int PlayersPositionX;
    
    PlayersPositionX=midpointx;
    
    return PlayersPositionX;
}

int Map::GetPlayersPositionY()
{
    int PlayersPositionY;
    
    PlayersPositionY=midpointy;
    
    return PlayersPositionY;
}

Map::Map()
{
    midpointx=430;
    midpointy=500;
    m=800;
    n=600;
    keyStrikeTime=0;
}
Map::~Map()
{
    
}

void Map::MoveMap()
{
    int r=9;
    if (midpointy>=n/2+r && midpointy<=png.hei-n/2-r)
    {
        if (key==FSKEY_UP)
        {
            midpointy+=r;
        }
        if (key==FSKEY_DOWN)
        {
            midpointy-=r;
        }
    }
    if (midpointy<n/2+r)
    {
        if (key==FSKEY_UP)
        {
            midpointy+=r;
        }
    }
    if (midpointy>png.hei-n/2-r)
    {
        if (key==FSKEY_DOWN)
        {
            midpointy-=r;
        }
    }
    
    if (midpointx>=m/2+r && midpointx<png.wid-m/2-r)
    {
        if (key==FSKEY_RIGHT)
        {
            midpointx+=r;
        }
        if (key==FSKEY_LEFT)
        {
            midpointx-=r;
        }
    }
    if (midpointx<m/2+r)
    {
        if (key==FSKEY_RIGHT)
        {
            midpointx+=r;
        }
    }
    if (midpointx>png.wid-m/2-r)
    {
        if (key==FSKEY_LEFT)
        {
            midpointx-=r;
        }
    }
    
}

void Map::DramMap()
{
    int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glRasterPos2d(0.0,(double)(winHei-1));
    
    unsigned char *p=png.rgba;
    int i,j;
    
    
    
    beginx=midpointx-m/2;
    beginy=midpointy-n/2;
    
	char *pp = new char[800*600*4];
    for (i=0; i<n; i++)
    {
        for (j=0; j<m; j++)
        {
            
            pp[(i*m+j)*4]=p[((i+beginy)*png.wid+j+beginx)*4];
            pp[(i*m+j)*4+1]=p[((i+beginy)*png.wid+j+beginx)*4+1];
            pp[(i*m+j)*4+2]=p[((i+beginy)*png.wid+j+beginx)*4+2];
            pp[(i*m+j)*4+3]=p[((i+beginy)*png.wid+j+beginx)*4+3];
        }
        
    }
    
    glDrawPixels(m,n,GL_RGBA,GL_UNSIGNED_BYTE,pp);
    MoveMap();
	
	delete [] pp;
    
}
void Map::RunMap()
{
	key = 0;
	int offset=0;
	char *story[] = { 
		"Welcome to CMU Adventure!",
		"Whether you have made up your mind to come to CMU or", 
		"you are still mulling over it, you are welcome to use", 
		"this game to have a glimpse of life at CMU.", 
		" ",
		"To familiarize yourself with the CMU environment,", 
		"navigate through the satellite view map of CMU campus ", // changes by Chun Fan
		"to explore all the buildings.", // changes by Chun Fan
		" ",
		"Studying constitutes a large part of CMU student life.",
		"CMU tries to make learning fun.See how MechE students", 
		"learn CAD & gear theory by playing the CAD & Gear games",
		"at Hammerschlag Hall and Hunts library.",
		" ",
		"Sometimes massive number of assignments could means ",
		"many sleepless nights. Play the StayAwake game to see", // changes by Chun Fan
		"how CMU lecturers and students fight off sleeping bugs",
		"during lectures in Margaret-Morrison Hall.",
		" ",
		"Student life is not just about studying, recreation is", 
		"essential too. Have some fun by playing the Pool game",
		"at University Center.",
		" ",
		"At CMU, safety is utmost important.CMU provides shuttle",
		"buses to ferry students and staffs back home safely.",
		"Play the Shuttle game at Porter Hall to have a feel on",
		"how it is like to catch a shuttle bus at CMU.",
		" ",
		"Press Enter to start game!"
		};

	Building building[5];	
	building[0].set("Uiversity Center", 1374, 1239,  110, 136);
	building[1].set("Hunts Hall", 1042, 662, 70, 35);
	building[2].set("Hammerschlag Hall", 454,  984,  111, 90);
	building[3].set("Porter Hall", 626,  805,  115, 75);
	building[4].set("Margaret-Morisson", 1489, 938,  50,  90);
		
    
	if(YSOK==png.Decode("instructions_background.png"))
    {
		// changes by Chun Fan
        //printf("Read Width=%d Height=%d\n",png.wid,png.hei);
        png.Flip();
    }
    else
    {
        printf("Read Error!\n");
        return ;
    }

	// Story Cover Page
	
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	int winWid,winHei;
	FsGetWindowSize(winWid, winHei);
	glRasterPos2d(0.0, (double)(winHei-1));
	glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	if(YSOK==png.Decode("map-with light.png"))
    {
		// changes by Chun Fan
        //printf("Read Width=%d Height=%d\n",png.wid,png.hei);
        png.Flip();
    }
    else
    {
        printf("Read Error!\n");
        return ;
    }

	glColor3ub(0,0,255);
	int n_line=1;
	glRasterPos2d(75,75);
	YsGlDrawFontBitmap20x32(story[0]);

	glColor3ub(0,0,0);
	for (int i=1; i<28; i++)
	{
		n_line++;			
		glRasterPos2d(75,75+16*n_line);
		YsGlDrawFontBitmap12x16(story[i]);
	}
	n_line++;
	glColor3ub(255,0,0);
	glRasterPos2d(75,75+16*n_line);
	YsGlDrawFontBitmap12x16(story[28]);

	FsSwapBuffers();
	
	
	while (key!=FSKEY_ENTER)
	{
		FsPollDevice();
		key = FsInkey();
		
		FsSleep(20);
	}

	
    
    key=FSKEY_NULL;
    int Mnumber=0;
    
    while(FSKEY_ESC!=key)
    {
        FsPollDevice();
        key=FsInkey();
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        if (key==FSKEY_M)
        {
            Mnumber++;
        }
        if (Mnumber%2==0)
        {
            DramMap();//Include check player's position(whether player can step on that part or not) and move
                      //the map.
            
            CheckPlayersState();
            
            player.DrawPlayerInMap();
            
            player.DrawMovingPlayerInCorner(player.PlayersState);
        }
        if (Mnumber%2==1)
        {
            ShowShrinkMap();
        }
		
		// check position
		int x=GetPlayersPositionX();
		int y=GetPlayersPositionY();
		//printf("x = %d,\t y = %d\n", x, y);

		srand((unsigned int)time(NULL) + rand());

		for (int i=0; i<5; i++)
		{
			int x_min = building[i].getX() - building[i].getW() ;
			int x_max = building[i].getX() + building[i].getW() ;
			int y_min = building[i].getY() - building[i].getH() ;
			int y_max = building[i].getY() + building[i].getH() ;
			if (x>x_min && x<x_max && y>y_min && y<y_max)
			{
				//char name[256];
				YsRawPngDecoder png4;
				int state0=0,state1=0,state2=0,state3=0,state4=0;

				FsPollDevice();
				
				int MouseEvent;

				int lb,mb,rb,mx,my;

				//building[i].getName(name);
				//printf("I am in %s!\n", name);
				switch (i)
				{
					case 0: // pool
                        if(YSOK==png4.Decode("ClickButton.png"))
                        {
                           png4.Flip();
                           int winWid,winHei;
                           FsGetWindowSize(winWid,winHei);
						   glRasterPos2d(400,300);
						   glDrawPixels(png4.wid,png4.hei,GL_RGBA,GL_UNSIGNED_BYTE,png4.rgba);
						   // changes by Chun Fan
						   //printf("%d  %d",png4.wid,png4.hei);					 
						}

						MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
						switch(MouseEvent)
						{
						case FSMOUSEEVENT_LBUTTONDOWN:
								if(mx>=400 && mx<=600 && my>=200 && my<=300)
								{
									state0=1;
								}
						}

						if(state0==1)
						{
							score.setResult(0, poolgame.rungame());
							// changes by Chun Fan
							//printf("Game 1: %d trials, %s\n", score.getCount(0), score.getResult(0)?"Passed":"Failed");
							FsClearEventQueue();
						}
						state0=0;
						//FsClearEventQueue();

						break;

					case 1: // CAD
						if(YSOK==png4.Decode("ClickButton.png"))
                        {
                           png4.Flip();
                           int winWid,winHei;
                           FsGetWindowSize(winWid,winHei);
						   glRasterPos2d(400,300);
						   glDrawPixels(png4.wid,png4.hei,GL_RGBA,GL_UNSIGNED_BYTE,png4.rgba);
						   // changes by Chun Fan
						   //printf("%d  %d",png4.wid,png4.hei);					 
						}

						MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
						switch(MouseEvent)
						{
						case FSMOUSEEVENT_LBUTTONDOWN:

								if(mx>=400 && mx<=600 && my>=200 && my<=300)
								{
									state1=1;
								}
						}

						if(state1==1)
						{
							
							score.setResult(1, cadclass.CADMain());
							// changes by Chun Fan
							//printf("Game 2: %d trials, %s\n", score.getCount(1), score.getResult(1)?"Passed":"Failed");
							FsClearEventQueue();
						}
						state1=0;		
						//FsClearEventQueue();

						break;

					case 2: // gear game
						if(YSOK==png4.Decode("ClickButton.png"))
                        {
                           png4.Flip();
                           int winWid,winHei;
                           FsGetWindowSize(winWid,winHei);
						   glRasterPos2d(400,300);
						   glDrawPixels(png4.wid,png4.hei,GL_RGBA,GL_UNSIGNED_BYTE,png4.rgba);
						   // changes by Chun Fan
						   //printf("%d  %d",png4.wid,png4.hei);					 
						}

						MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
						switch(MouseEvent)
						{
						case FSMOUSEEVENT_LBUTTONDOWN:
								if(mx>=400 && mx<=600 && my>=200 && my<=300)
								{
									state2=1;
								}
						}

						if(state2==1)
						{
						   score.setResult(2, geargame.run());
						   // changes by Chun Fan
						   //printf("Game 3: %d trials, %s\n", score.getCount(2), score.getResult(2)?"Passed":"Failed");
						   
							// changes by Chun Fan
						    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
							FsClearEventQueue();
						}
						state2=0;
						//FsClearEventQueue();

						break;

					case 3:
						if( score.getGraduate())
						{
							if(YSOK==png4.Decode("ClickButton.png"))
							{
							   png4.Flip();
							   int winWid,winHei;
							   FsGetWindowSize(winWid,winHei);
							   glRasterPos2d(400,300);
							   glDrawPixels(png4.wid,png4.hei,GL_RGBA,GL_UNSIGNED_BYTE,png4.rgba);
							   // changes by Chun Fan
							   //printf("%d  %d",png4.wid,png4.hei);					 
							}

							MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
							switch(MouseEvent)
							{
							case FSMOUSEEVENT_LBUTTONDOWN:
									if(mx>=400 && mx<=600 && my>=200 && my<=300)
									{
										state3=1;
									}
							}
						}

						if(state3==1 )
						{
						   shuttle.action();

							glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

							score.DrawScoreCard();

							FsSwapBuffers();
							
							FsPollDevice();
							int key1 = FsInkey();
							
							while(key1!=FSKEY_ENTER)
							{
								
								FsPollDevice();
								key1 = FsInkey();
								FsSleep(20);
							}
							
							glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

							awardStage.SetDept("Mechanical Engineering");

							awardStage.DrawStage();
							awardStage.PrintCert();

							FsSwapBuffers();						
							
							FsPollDevice();
							key1 = FsInkey();
							
							while(key1!=FSKEY_ENTER)
							{
								FsPollDevice();
								key1 = FsInkey();
								
								FsSleep(20);
							}
							key=FSKEY_ESC;

						}
						state3=0;
				
						//if (checkscore()==1)		
						FsClearEventQueue();

						break;

					case 4: // stayawake
						if(YSOK==png4.Decode("ClickButton.png"))
                        {
                           png4.Flip();
                           int winWid,winHei;
                           FsGetWindowSize(winWid,winHei);
						   glRasterPos2d(400,300);
						   glDrawPixels(png4.wid,png4.hei,GL_RGBA,GL_UNSIGNED_BYTE,png4.rgba);
						   // changes by Chun Fan
						   //printf("%d  %d",png4.wid,png4.hei);					 
						}

						MouseEvent=FsGetMouseEvent(lb,mb,rb,mx,my);
						switch(MouseEvent)
						{
						case FSMOUSEEVENT_LBUTTONDOWN:
								if(mx>=400 && mx<=600 && my>=200 && my<=300)
								{
									state4=1;
								}
						}

						if(state4==1)
						{
						   stayawake.StartGame();
						   score.setResult(3, stayawake.GetScore());
						   // changes by Chun Fan
						   //printf("Game 4: %d trials, %s\n", score.getCount(3), score.getResult(3)?"Passed":"Failed");
							FsClearEventQueue();
						}
						state4=0;
						//FsClearEventQueue();

						break;
					
				}
			}
		}
		
        FsSwapBuffers();
        FsSleep(50);
    }
}
