#ifndef MAP_CLASS_IS_INCLUDED
#define MAP_CLASS_IS_INCLUDED

#include "Player.h"
#include "Building.h" 
#include "playgame.h"
#include "keepAwake.h"
#include <time.h>
#include "pool.h"
#include "ParserClass.h"
#include "FileClass.h"
#include "gearGame.h"
#include "CAD-head.h"
#include "awardStage.h"
#include "score.h"

class Map
{
protected:
    YsRawPngDecoder png;
    Player player;
    int key,keyStrikeTime;
    int midpointx,midpointy;
    int beginx,beginy;
    int m,n;
	playgame shuttle;
	KeepAwake stayawake;
	PoolGame poolgame;
	gearGame geargame;
	CADCLASS cadclass;
	AwardStage awardStage;
	Score score;
    
public:
    Map();
    ~Map();
    void RunMap(void);
    void DramMap(void);
    void MoveMap(void);
    void ShowShrinkMap(void);
    void RunSmallMap(void);
    void CheckPlayerPosition();//using this memberfunction to know if the player can move 
    int GetPlayersPositionX();//the mid point of the map
    int GetPlayersPositionY();
    void CheckPlayersState();

};

#endif
