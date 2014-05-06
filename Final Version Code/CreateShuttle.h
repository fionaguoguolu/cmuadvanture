//
//  CreateShuttle.h
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/13.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#ifndef __TEST__CreateShuttle__
#define __TEST__CreateShuttle__

#include <iostream>
#include "Node2D.h"
#include "StringParser.h"
#include "CreateShuttle.h"
#include "fssimplewindow.h"
#include "yspng.h"
using namespace std;

class CreateShuttle
{
public:
    YsRawPngDecoder busfront;
    YsRawPngDecoder busside;
    int state;
    //int X,Y;
    char *str;
    Node2D *node;
    int nNode;
    
    CreateShuttle();
    ~CreateShuttle();
    void move(int, const int & step);
    void action(int, int & step, int & state);
    int Readfile(const char []);
    void CleanUp();
	void Set();
    void AllocNode(int n);
    int Writefile(FILE *fp,char *str);
    int checkhome (const int &step );
    
    
};


#endif /* defined(__TEST__CreateShuttle__) */
