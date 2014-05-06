#ifndef SCORE_IS_INCLUDED
#define SCORE_IS_INCLUDED

class Score 
{
private:
	int winWid, winHei;
	YsRawPngDecoder scoreCard;
	int gameCount[4];
	int gamePassed[4];
	int graduate;

public:
	Score(void);
	~Score(void);
	int setResult(int game, int passed);
	int getCount(int game);
	int getResult(int game);
	int getGraduate();

	void DrawScoreCard(void);
};

#endif