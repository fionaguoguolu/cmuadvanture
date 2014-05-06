#ifndef QUESTION_CLASS_IS_INCLUDED
#define QUESTION_CLASS_IS_INCLUDED

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "gear.h"
#include "ysglfontdata.h"

class question
{
protected:
	gear *allGear;
	int nGear;
	int *gearTrain;
	int *missingGear;
	gear *gearChoice;
	int gearClicked;	// changes by Chun Fan
	int nChoice;
	int *gearInstalled;
	int nInstalled;
	double inputSpeed;
	int answered;
	int correct;
	
public:
	question();
	~question();
	void cleanUp();
	void createGear(int nGear_i, double inputSpeed_i, int nTeeth[], 
		double x[], double y[], double theta[], int gearTrain_i[]);
	void prepareQuestion();
	void displayQuestion();
	void displayGear();
	void displayChoice();
	void displayAnnotation();
	void displayAnswer();
	void getUserInput();
	void checkAnswer();
	int getResults() const; 
	int getAnswered() const; 
	void calculateSpeed();
	void animateGears(double dt);	
};

#endif