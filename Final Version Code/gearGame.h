#ifndef GEAR_GAME_CLASS_IS_INCLUDED
#define GEAR_GAME_CLASS_IS_INCLUDED

#include "ParserClass.h"
#include "FileClass.h"
#include "question.h"
#include "yspng.h"

class gearGame{
protected:
	int nQuestion;
	question *gearQuestion;
	char** questionCaption;
	ParserClass strParser;
	FileClass file;
	int *nTeeth;
	double *x, *y, *theta;
	int *relation;
	YsRawPngDecoder png;	// changes by Chun Fan
	
public: 
	gearGame();
	~gearGame();
	
	int read(char fstr[]);
	int run();
	void displayInstruction();
	void displayQuestionNumber(int QuestionNumber);
	int displayScores();
	void displayBackground();
	int getScore();
	void cleanup();
	void partialCleanup();
};

#endif