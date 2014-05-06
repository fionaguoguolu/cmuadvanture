//
//  Badguy.cpp
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/17.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#include "Badguy.h"
#include <iostream>
using namespace std;

void Createbadguy::set()
{

	dt=1;
    for (int i=0; i<4; i++)
    {
        x[i]=675+i*30;
        y[i]=300+i*40;
        vx[i]=10;
    }
}



void Createbadguy::Move(void)
{
    for (int i=0; i<4; i++)
    {
        x[i]=x[i]+vx[i]*dt;
    }
}
void Createbadguy::Draw()
{
    badguy.Decode("badguy.PNG");
    badguy.Flip();
    for (int i=0; i<4; i++)
    {
        
        glRasterPos2d(x[i],(double)(badguy.hei-1)+y[i]);
        glDrawPixels(badguy.wid,badguy.hei,GL_RGBA,GL_UNSIGNED_BYTE,badguy.rgba);
        
        /*glColor3ub(255,0,0);
        glBegin(GL_QUADS);
        glVertex2i(x[i],y[i]);
        glVertex2i(x[i]+20,y[i]);
        glVertex2i(x[i]+20,y[i]-20);
        glVertex2i(x[i],y[i]-20);
        glEnd();
         */
    }
}
void Createbadguy::Bounce()
{
    
    for (int i=0; i<4; i++)
    {
        if(x[i]<680 && vx[i]<0.0)
        {
            vx[i]=-vx[i];
        }
        else if(x[i]>790 && vx[i]>0.0)
        {
            vx[i]=-vx[i];
        }
    }
}
int Createbadguy::checkuser(int xvalue, int yvalue)
{
    yvalue=600-yvalue;
    for (int i=0; i<4; i++)
    {
        if (xvalue>x[i] && xvalue<x[i]+20 && yvalue<y[i] && yvalue>y[i]-20)
            return 1;
    }

}

void Createbadguy::action(int & state,int xvalue, int yvalue)
{
    Move();
    Bounce();
    Draw();
    if (checkuser(xvalue,yvalue)==1)
        state=3;
}




