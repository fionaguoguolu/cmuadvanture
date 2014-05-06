#include "Map.h"
#include "keepAwake.h"



int main(void)
{
    FsOpenWindow(16,16,800,600,1);
    
	Map map;
    map.RunMap();
    /*
	int x=map.GetPlayersPositionX();
    int y=map.GetPlayersPositionY();
    
    printf("x=%d,y=%d",x,y);
    */
	//KeepAwake stayawake;
	//stayawake.StartGame();
	return 0;
}