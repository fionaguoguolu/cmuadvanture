//
//  Badguy.h
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/17.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#ifndef __TEST__Badguy__
#define __TEST__Badguy__

#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
class Createbadguy
{
public:
    int x[4],y[4],vx[4],dt;
    YsRawPngDecoder badguy;
    void Move();
    void Draw();
    void Bounce();
    void action(int &,int,int);
    void set();
    int checkuser(int,int);
    
};

#endif /* defined(__TEST__Badguy__) */
