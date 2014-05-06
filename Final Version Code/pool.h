#include<stdio.h>
#include<math.h>
#include"fssimplewindow.h"
#include"ysglfontdata.h"
#include"yspng.h"
#include<time.h>
#include<ctype.h>
class PoolGame{

public:
	int rungame(void);
	PoolGame();
	//~PoolGame();
	void ExitGame(int win);
	void DrawTable() const;
	void DrawPowerBar(int power);
	void DrawIntroScreen() const;
	void DrawBalls() const;
	void MoveBalls(void);
	void CalcCueHit(int x,int y, float power);
	void DrawCircle(int x,int y,int rad) const;
	void CollisionCheck();
	void bounce();
	void DrawTime(int time);
	float distance(int x1,int y1,int x2, int y2) const;
	int Ballstop();
	void AfterCollision(float x1, float y1,float vx1,float vy1, float x2, float y2,float vx2,float vy2,float rad,int i,int j);
	void DrawCue(int x, int y) const;
	float magnitude(float x,float y) const;
	void checkPocket();
	int gamestate;
protected:
	float BallPos[16][16];
	float BallVel[16];
	float dirVector[16][16];
	int BallsHit,cueHit;
	int timelimit;
	float radius[16],mass[16];
	int score, playtime,state;
	

};