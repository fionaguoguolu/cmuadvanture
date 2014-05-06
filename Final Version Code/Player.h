#ifndef PLAYER_CLASS_IS_INCLUDED
#define PLAYER_CLASS_IS_INCLUDED

#include <stdio.h>
#include <math.h>
#include "yspng.h"
#include "fssimplewindow.h"

const double YS_PI=3.1415927;

class Player
{
public:
    
    int PlayersState;
    int KeySignalstate;
    
    void DrawPlayerInMap();
    void DrawMovingPlayerInCorner(int PS);// unfinised

};

#endif