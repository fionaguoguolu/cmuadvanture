#ifndef YYKEEPAWAKE_IS_INCLUDED
#define YYKEEPAWAKE_IS_INCLUDED

#include "yspng.h"
#include "questionClass.h"
#include "dusterClass.h"
#include "distractionClass.h"

#define YY_NQUESTION 10
#define YY_NPNG 11
#define YY_NDISTRACTION 10
#define YY_NDUSTER 20


class KeepAwake
{
private:
	int YY_passKeepAwake;
	int startTime;

	int nCorrectQn;
	int nDusterCaught;

	YsRawPngDecoder bkgd;
	void LoadBkgd(void);

	YsRawPngDecoder play;
	void LoadGameMenu(void);

	QuestionClass *questions;
	void LoadQuestions(void);

	DusterClass duster;

	char* *dPNG;
	void RandomSetPNG(const int i, const int r);
	void LoadDistractionsPNG(void);

	DistractionClass *distractions;
	void LoadDistractionClass(void);
	
	YsRawPngDecoder correct1;
	YsRawPngDecoder correct2;
	YsRawPngDecoder wrong1;
	YsRawPngDecoder wrong2;
	void LoadSojiPNG(void);

	//void StartGame(void);
	void DrawBkgd(void) const;
	void DrawGameMenu(const int MenuX, const int MenuY);
	bool IsPlayButtonClicked(const int MenuX, const int MenuY,  const int mx, const int my, const int lb);
	
	void PlayGame(void);
	void DisplayMsg(const char msg[], const int x, const int y, const int r, const int g, const int b) const;

	void DrawSoji(const bool correctAnswer) const;

	void UpdateDistractions(const int mx, const int my, const int lb, const int timeNow);

	int UpdateDuster(const int mx, const int my, const int lb, const int duster_startTime, const int timeNow);
	void DrawCircle(const int cx, const int cy, const int rad);
	int ExplodeDuster(const int startTime, const int timeNow);
	
	void DisplayScore(void);
	void DisplayTime(const int startTime, const int timeNow);
	void DisplayFinalScore(void);

	void Score(void);

	void Initialize(void);

public:
	KeepAwake(void);
	~KeepAwake(void);

	void StartGame(void);

	int GetScore(void) const;
	
};

#endif