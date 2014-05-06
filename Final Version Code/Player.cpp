#include "Player.h"

void Player::DrawMovingPlayerInCorner(int PS)
{
    
    if (PS==0)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("1.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }

    }
    if (PS==1)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("2.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    if (PS==2)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("3.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    if (PS==3)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("4.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    if (PS==4)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("5.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    if (PS==5)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("6.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    if (PS==6)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("7.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    if (PS==7)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("8.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    if (PS==8)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("9.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    if (PS==9)
    {
        YsRawPngDecoder png1;
        if(YSOK==png1.Decode("10.png"))
        {
            png1.Flip();
            int winWid,winHei;
            FsGetWindowSize(winWid,winHei);
            glRasterPos2d(0.0,(double)(winHei-1));
            glDrawPixels(png1.wid,png1.hei,GL_RGBA,GL_UNSIGNED_BYTE,png1.rgba);
        }
        
    }
    
}


void Player::DrawPlayerInMap()
{
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
    int i;
    int cx=400,cy=300,rad=15;
    for(i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32.0;
        double x=(double)cx+cos(angle)*(double)rad;
        double y=(double)cy+sin(angle)*(double)rad;
        glVertex2d(x,y);
    }
    
    glEnd();
}
