//
//  playgame.cpp
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/19.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#include "playgame.h"

playgame::playgame(void)
{
    set();
}

playgame::~playgame(void)
{
    
}
void playgame::set(void)
{
    cleanup();
    Numofmouse=0;
    state=0;
    numyeah=20;
    judge=0;
    xcar=100;
    ycar=260;
    xrunner=10;
    yrunner=285;
    dt=1;
    vxcar=21;
    vxrunner=23;
    
    
}
void playgame::cleanup()
{
    
}
void playgame::Move(void)
{
        xcar=xcar+vxcar*dt;
        xrunner=xrunner+vxrunner*dt;
}
void playgame::Bounce(void)
{
    
    if(xcar>800)
    {
        xcar=100;
    }
    
    if(xrunner>800)
    {
        xrunner=20;
    }
    
    
}
void playgame::drawintro(int state,int &judge)
{
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glColor3ub(0,0,0);
    
    YsRawPngDecoder car;
    car.Decode("bussidebig.PNG");
    car.Flip();
    YsRawPngDecoder runner;
    switch (judge)
    {
        case 0:
            runner.Decode("runnerbig1.PNG");
            judge=1;
            break;
        case 1:
            runner.Decode("runnerbig2.PNG");
            judge=2;
            break;
        case 2:
            runner.Decode("runnerbig3.PNG");
            judge=0;
            break;   
    }
    runner.Flip();
    
    Move();
    Bounce();
    glRasterPos2d(xcar,(double)(car.hei-1)+ycar);
    glDrawPixels(car.wid,car.hei,GL_RGBA,GL_UNSIGNED_BYTE,car.rgba);
    glRasterPos2d(xrunner,(double)(runner.hei-1)+yrunner);
    glDrawPixels(runner.wid,runner.hei,GL_RGBA,GL_UNSIGNED_BYTE,runner.rgba);
    
    glRasterPos2d(190,40);
    YsGlDrawFontBitmap20x32("~CHASING THE SHUTTLE~");
    
    
    glRasterPos2d(290,85);
    YsGlDrawFontBitmap20x28("Introdution:");
    glRasterPos2d(100,100);
    YsGlDrawFontBitmap12x16("Please control the people and catch the shuttle. You");
    glRasterPos2d(100,120);
    YsGlDrawFontBitmap12x16("will need to go into the station square in order to ");
    glRasterPos2d(100,140);
    YsGlDrawFontBitmap12x16("catch the shuttle. ");
    
    if ((judge%2)==0)
    {
        glRasterPos2d(70,180);
        YsGlDrawFontBitmap12x16("** Be careful of the Bad Guy, they will kill you so that");
        glRasterPos2d(70,200);
        YsGlDrawFontBitmap12x16("   you can't graduate alive... ");
    }
    
    if (state==4)
    {
        glColor3ub(255,0,0);
        glRasterPos2d(70,450);
        YsGlDrawFontBitmap12x16("....You lose, press space to start again !!");
    }
    
    glColor3ub(0,0,0);
    glRasterPos2d(220,400);
    YsGlDrawFontBitmap20x32("Press Space to Start");
    glBegin(GL_LINE_STRIP);
    int length=260,width=40, Xorighin=400, Yorigin=380;
    glVertex2i(Xorighin-length,Yorigin+width);
    glVertex2i(Xorighin+length,Yorigin+width);
    glVertex2i(Xorighin+length,Yorigin-width);
    glVertex2i(Xorighin-length,Yorigin-width);
    glVertex2i(Xorighin-length,Yorigin+width);
    glEnd();
    
}
void playgame::drawend(int & i)
{
	YsRawPngDecoder End;
	End.Decode("End_2.png");
	End.Flip();
	YsRawPngDecoder Homeguy;
	Homeguy.Decode("homeguy.png");
	Homeguy.Flip();
	YsRawPngDecoder Home;
	Home.Decode("HOME.png");
	Home.Flip();
	glRasterPos2d(0,(double)(End.hei-1));
    glDrawPixels(End.wid,End.hei,GL_RGBA,GL_UNSIGNED_BYTE,End.rgba);



	if (i<=3)
	{
		glRasterPos2d(235+10*i,(double)(Homeguy.hei-1)+(350-i*10));
		glDrawPixels(Homeguy.wid,Homeguy.hei,GL_RGBA,GL_UNSIGNED_BYTE,Homeguy.rgba);
	}else
	{
		glRasterPos2d(235+10*3,(double)(Homeguy.hei-1)+(350-3*10));
		glDrawPixels(Homeguy.wid,Homeguy.hei,GL_RGBA,GL_UNSIGNED_BYTE,Homeguy.rgba);
		glRasterPos2d(100,(double)(Home.hei-1)+100);
		glDrawPixels(Home.wid,Home.hei,GL_RGBA,GL_UNSIGNED_BYTE,Home.rgba);
	}
	i++;



}
void playgame::drawwhite(int step,YsRawPngDecoder &png)
{
    
    if (step>235)
    {
        for (int j=252; j>175; j--)
        {
            for (int i=277; i<310; i++)
            {
                png.rgba[4*((600-j)*(png.wid)+i)+0]=255;
                png.rgba[4*((600-j)*(png.wid)+i)+1]=255;
                png.rgba[4*((600-j)*(png.wid)+i)+2]=204;
            }
        }
    }
    
    
    if (step>327)
    {
        for (int j=254; j>175; j--)
        {
            for (int i=425; i<466; i++)
            {
                png.rgba[4*((600-j)*(png.wid)+i)+0]=255;
                png.rgba[4*((600-j)*(png.wid)+i)+1]=255;
                png.rgba[4*((600-j)*(png.wid)+i)+2]=204;
            }
            
        }
    }
    
    if (step>235)
    {
        for (int j=341; j>315; j--)
        {
            for (int i=490; i<555; i++)
            {
                png.rgba[4*((600-j)*(png.wid)+i)+0]=255;
                png.rgba[4*((600-j)*(png.wid)+i)+1]=255;
                png.rgba[4*((600-j)*(png.wid)+i)+2]=204;
            }
        }
    }
}
void playgame::pngprocessiong(YsRawPngDecoder &png)
{
    int winWid,winHei;
    FsGetWindowSize(winWid,winHei);
    glViewport(0,0,winWid,winHei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)winWid-1,(float)winHei-1,0,-1,1);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    FsGetWindowSize(winWid,winHei);
    glRasterPos2d(0.0,(double)(png.hei-1));
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
    
}

void playgame::action()
{
    
    set();
    YsRawPngDecoder png;
    png.Decode("123.PNG");
    png.Flip();
    FsOpenWindow(16,16,png.wid,png.hei,1);
    badguy.set();

    
    if(0!=shuttle.Readfile("shuttle.txt"))
    {
        while ((state==0)||(state==4))
        {
            while (key!=FSKEY_SPACE)
            {
                drawintro(state,judge);
                
                
                
                key=FsInkey();
                FsPollDevice();
                FsSwapBuffers();
                FsSleep(200);
                
            }
            YsRawPngDecoder png;
            png.Decode("123.PNG");
            png.Flip();
            step=0;
            state=0;
            CreateUser user;
            int countdownNum=50;
            
            while ((state==0)||(state==1)||(state==3))
            {
                pngprocessiong(png);
                drawwhite(step,png);
                key=FsInkey();
                user.action(key,state,step,numyeah,png,shuttle.node);
                badguy.action(state,user.X,user.Y);
                shuttle.action(key,step,state);
                
                if (state==3)
                {
                    countdownNum--;
                    if (countdownNum==1)
                    {
                        state=4;
                    }
                }
                FsPollDevice();
                FsSwapBuffers();
                FsSleep(100);
            }
        }
    }
    int i=0;
    while (10!=i)
    {
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		drawend(i);

        key=FsInkey();
        FsPollDevice();
        FsSwapBuffers();
        FsSleep(1000);
        
    }

}