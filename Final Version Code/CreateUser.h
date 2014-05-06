//
//  CreateUser.h
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/13.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#ifndef __TEST__CreateUser__
#define __TEST__CreateUser__

#include <iostream>
#include "yspng.h"
#include "CreateShuttle.h"
#include "fssimplewindow.h"
using namespace std;
class CreateUser
{
public:
    int state;
    int X,Y;
    int runnerstatus;
    YsRawPngDecoder user;
    
    CreateUser();
    ~CreateUser();
    void move(int,YsRawPngDecoder &);
    void draw(void);
    void action(int,int &,int,int &,YsRawPngDecoder &png, Node2D *node);
    void drawyeah(char[]);
    int checkshuttle(int , Node2D *node);
    int checkhome();
};



#endif /* defined(__TEST__CreateUser__) */
