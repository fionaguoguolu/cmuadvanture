//
//  CreateUser.cpp
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/13.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#include "CreateUser.h"
#include "ysglfontdata.h"




CreateUser::CreateUser()
{
    X=400;
    Y=40;
    runnerstatus=1;
}

CreateUser::~CreateUser()
{
    
}


void CreateUser::move(int key,YsRawPngDecoder &png)
{
    int X1=X;
    int Y1=Y;
    int step=5;
    int tempup;
    int tempdown;
    int tempright;
    int templeft;
    //int num;
    //num=(png.hei-(600-Y))*(png.wid)+X;
        switch (key)
        {
            case FSKEY_LEFT:
                tempup=(Y1)*(png.wid)+X1;
                tempdown=(Y1-31)*(png.wid)+X1;
                if (png.rgba[(tempup)*4+0]==255 && png.rgba[(tempup)*4+1]==255 && png.rgba[(tempup)*4+2]==204 && png.rgba[(tempdown)*4+0]==255 && png.rgba[(tempdown)*4+1]==255 && png.rgba[(tempdown)*4+2]==204)
                {
                    X=X-step;
                }
                
                runnerstatus++;
                if (runnerstatus>3)
                    runnerstatus=1;
                break;
            case FSKEY_RIGHT:
                tempup=(Y1)*(png.wid)+X1+23;
                tempdown=(Y1-31)*(png.wid)+X1+23;
                if (png.rgba[(tempup)*4+0]==255 && png.rgba[(tempup)*4+1]==255 && png.rgba[(tempup)*4+2]==204 && png.rgba[(tempdown)*4+0]==255 && png.rgba[(tempdown)*4+1]==255 && png.rgba[(tempdown)*4+2]==204)
                {
                    X=X+step;
                }
                
                runnerstatus++;
                if (runnerstatus>3)
                    runnerstatus=1;
                break;
            case FSKEY_UP:
                tempright=(Y1)*(png.wid)+X1+23;
                templeft=(Y1)*(png.wid)+X1;
                if (png.rgba[(tempright)*4+0]==255 && png.rgba[(tempright)*4+1]==255 && png.rgba[(tempright)*4+2]==204 && png.rgba[(templeft)*4+0]==255 && png.rgba[(templeft)*4+1]==255 && png.rgba[(templeft)*4+2]==204)
                {
                    Y=Y+step;
                }
                runnerstatus++;
                if (runnerstatus>3)
                    runnerstatus=1;
                break;
            case FSKEY_DOWN:
                tempright=(Y1-31)*(png.wid)+X1+23;
                templeft=(Y1-31)*(png.wid)+X1;
                if (png.rgba[(tempright)*4+0]==255 && png.rgba[(tempright)*4+1]==255 && png.rgba[(tempright)*4+2]==204 && png.rgba[(templeft)*4+0]==255 && png.rgba[(templeft)*4+1]==255 && png.rgba[(templeft)*4+2]==204)
                {
                    Y=Y-step;
                }
                runnerstatus++;
                if (runnerstatus>3)
                    runnerstatus=1;
        }
    

    
    
};
void CreateUser::draw(void)
{
    int Xchange=X;
    int Ychange=600-Y;
    
    switch (runnerstatus)
    {
        case 1:
            user.Decode("runner1.PNG");
            //runnerstatus=2;
            break;
        case 2:
            user.Decode("runner2.PNG");
            //runnerstatus=3;
            break;
        case 3:
            user.Decode("runner3.PNG");
            //runnerstatus=1;
            break;
            

    }
    
    //user.Decode("runner.PNG");
    user.Flip();
    glRasterPos2d(Xchange,(double)(user.hei-1)+Ychange);
    glDrawPixels(user.wid,user.hei,GL_RGBA,GL_UNSIGNED_BYTE,user.rgba);
    
    /*
    glColor3ub(255,255,0);
    glBegin(GL_QUADS);
    glVertex2i(Xchange,Ychange);
    glVertex2i(Xchange+10,Ychange);
    glVertex2i(Xchange+10,Ychange-10);
    glVertex2i(Xchange,Ychange-10);
    glEnd();
     */
    
    
};
void CreateUser::drawyeah(char a[])
{
    
    int Xchange=X;
    int Ychange=600-Y;
    
    glColor3ub(0,0,0);
    glRasterPos2d(Xchange,Ychange);
    YsGlDrawFontBitmap16x20(a);
    
    
};
int CreateUser::checkshuttle(int step,Node2D *node)
{
    if ((X>19 && X<102 && Y>441 && Y<487)||(X>332 && X<400 && Y>476 && Y<501)||(X>486 && X<553 && Y>492 && Y<523))
    {
        
    
        if ( (X<=20+((node+step)->x)) && (X>=-20+((node+step)->x)) && (600-Y<=20+((node+step)->y))&& (600-Y>=-20+((node+step)->y)))
        {
            return 1;
        }else
            return 0;
    }
};

int CreateUser::checkhome(void)
{
    if (X>675 && X<800 && Y>0 && Y<(600-492))
        return 1;
    
};


void CreateUser::action(int key,int & state,int step,int & nyeah,YsRawPngDecoder &png,Node2D *node)
{
    switch (state)
    {
        case 0:   //1=still looking for shuttle
        {
            move(key,png);
            draw();
            if (checkshuttle(step,node)==1)
            {
                drawyeah("Yeah!!");
                state=1;
            }else if(checkhome()==1)
            {
                state=2;
            }
        }
            break;
        case 1:   // ppl in shuttle
        {
            if (nyeah>1)
                drawyeah("Yeah!!");
            nyeah--;
            break;
        }
        case 3:  // ppl fail (killed by bad guy)
        {
            drawyeah("OH~NO~");
        }
    }

};