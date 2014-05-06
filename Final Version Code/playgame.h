//
//  playgame.h
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/19.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#ifndef __TEST__playgame__
#define __TEST__playgame__

#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"
#include "CreateShuttle.h"
#include "CreateUser.h"
#include "Badguy.h"


class playgame
{
public:
    
    Createbadguy badguy;
    CreateShuttle shuttle;
    CreateUser user;
    int key;
    int Numofmouse;
    int state;
    int numyeah;
    int judge;
    int step;
    int xcar,ycar;
    int xrunner,yrunner;
    int vxcar,vxrunner,dt;
    
    playgame();
    ~playgame();
    void action();
    void drawintro(int state,int &judge);
    void drawwhite(int step,YsRawPngDecoder &png);
    void set();
    void cleanup();
    void pngprocessiong(YsRawPngDecoder &png);
    void Move();
    void Bounce();
	void drawend(int &);
    
};

#endif /* defined(__TEST__playgame__) */
