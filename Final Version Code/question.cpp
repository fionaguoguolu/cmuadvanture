#include "question.h"

question::question()
{
	allGear = NULL;
	nGear = 0;
	gearTrain = NULL;
	missingGear = NULL;
	gearChoice = NULL;
	gearClicked = -1;	// changes by Chun Fan
	nChoice = 0;
	gearInstalled = NULL;
	nInstalled = 0;
	inputSpeed = 0;
	answered = 0;
	correct = 0;
	srand(time(NULL));
}

question::~question()
{
	cleanUp();
}

void question::cleanUp()
{
	if (allGear!=NULL)
	{
		delete [] allGear;
	}
	nGear = 0;
	if (gearTrain!=NULL)
	{
		delete [] gearTrain;
	}
	if (missingGear!=NULL)
	{
		delete [] missingGear;
	}
	if (gearChoice!=NULL)
	{
		delete [] gearChoice;
	}
	nChoice = 0;
	gearClicked = -1;	// changes by Chun Fan
	if (gearInstalled!=NULL)
	{
		delete [] gearInstalled;
	}
	nInstalled = 0;
	answered = 0;
	correct = 0;
}

void question::createGear(int nGear_i, double inputSpeed_i, int nTeeth[], 
	double x[], double y[], double theta[], int gearTrain_i[])
{
	if (allGear==NULL && gearTrain==NULL)
	{
		nGear = nGear_i;
		inputSpeed = inputSpeed_i;
		allGear = new gear[nGear];
		gearTrain = new int[nGear];
		missingGear = new int[nGear];
		
		for (int i=0; i<nGear; i++)
		{
			// set N 
			allGear[i].setN(nTeeth[i]);
			
			// set color
			allGear[i].setColor(rand()%127,rand()%127,rand()%127);
			
			// set position
			allGear[i].setPosition(x[i],y[i],theta[i]);
			
			gearTrain[i] = gearTrain_i[i];
		}
	}
}

void question::prepareQuestion()
{
	nChoice = 0;
	missingGear[0] = 0;
	while (nChoice == 0)
	{
		for (int i=1; i<nGear-1; i++)
		{
			missingGear[i] = rand()%2;
			// changes by Chun Fan
			//printf("Gear %d: Missing: %d\n", i, missingGear[i]);
			nChoice += missingGear[i];
		}
	}
	missingGear[nGear-1] = 0;
	
	gearChoice = new gear[nChoice];
	gearInstalled = new int[nChoice];
	int j=0;
	for (int i=1; i<nGear-1; i++)
	{
		if(missingGear[i] == 1)
		{
			gearChoice[j] = allGear[i];
			gearChoice[j].setPosition(100, 
				(j+1)*600.0/(double)(nChoice+1), 0);
			gearChoice[j].setColor(rand()%127, rand()%127, rand()%127);
			
			gearInstalled[j] = 0;
			
			j++;
		}
	}
}

void question::displayQuestion()
{
	displayGear();
	displayChoice();
	displayAnnotation();
	displayAnswer();
}

void question::displayGear()
{
	for (int i=0; i<nGear; i++)
	{
		if (missingGear[i]==0)
			allGear[i].draw();
		else
		{
			// draw axis only
			glColor3ub(0,0,0);
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(1, 0xf0f0);
			glBegin(GL_LINE_LOOP);
			double rad = (double)(rand()%100);
			int nSector = (int)(2*Pi*rad/1);
			double d_angle = 2*Pi/nSector;
			for (int j=0; j<nSector; j++)
				glVertex2d(allGear[i].getX() + rad*cos(j*d_angle), 
					allGear[i].getY() + rad*sin(j*d_angle));
			glEnd();
			glDisable(GL_LINE_STIPPLE);
		}
	}
}

void question::displayChoice()
{
	for (int i=0; i<nChoice; i++)
	{
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (!correct)
		{
			gearChoice[i].draw();
		}
		
		//glDisable(GL_BLEND);
	}
}

void question::displayAnnotation()
{
	char str[256];
	
	// display input gear 	
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(allGear[0].getX(), allGear[0].getY());
	glVertex2d(250+42, 550-16-15);
	glEnd();
	glRasterPos2d(250, 550-5);	
	YsGlDrawFontBitmap12x16("Input:");
	glRasterPos2d(250, 550+5+16);
	sprintf(str, "%.2lf rad/s", allGear[0].getSpeed());
	YsGlDrawFontBitmap12x16(str);
	
	// display output gear 	
	
	glColor3ub(0,0,255);
	glBegin(GL_LINES);
	glVertex2d(allGear[nGear-1].getX(), allGear[nGear-1].getY());
	glVertex2d(250+42+350, 550-16-15);
	glEnd();
	glRasterPos2d(250+350, 550-5);	
	YsGlDrawFontBitmap12x16("Output:");
	glRasterPos2d(250+350, 550+5+16);
	sprintf(str, "%.2lf rad/s", allGear[nGear-1].getSpeed());
	YsGlDrawFontBitmap12x16(str);
}

void question::displayAnswer()
{
	if(answered)
	{
		if (correct)
		{
			glColor3ub(255,255,0);
			int x=550;
			int y=65;
			glBegin(GL_QUADS);
			glVertex2d(x-20, y-52);
			glVertex2d(x+170, y-52);
			glVertex2d(x+170, y+20);
			glVertex2d(x-20, y+20);
			glEnd();			
			glColor3ub(0,0,255);
			glRasterPos2d(x, y);
			YsGlDrawFontBitmap20x32("You Win!");		
		}
		else
		{
			glColor3ub(255,255,0);
			int x=550;
			int y=65;
			glBegin(GL_QUADS);
			glVertex2d(x-30, y-52);
			glVertex2d(x+200, y-52);
			glVertex2d(x+200, y+20);
			glVertex2d(x-30, y+20);
			glEnd();
			glColor3ub(255,0,0);
			glRasterPos2d(x, y);
			YsGlDrawFontBitmap20x32("You Lose!");
		}
	}
}

void question::getUserInput()
{
	if (answered == 0)
	{
		int lb,mb,rb,mx,my, mouseEvent;
		mouseEvent = FsGetMouseEvent(lb,mb,rb,mx,my);	
		if(lb)
		{
			// changes by Chun Fan
			if (gearClicked == -1)
			{
				for (int i=0; i<nChoice; i++)
				{
					if ((sqrt((mx-gearChoice[i].getX())*(mx-gearChoice[i].getX())+
						(my-gearChoice[i].getY())*(my-gearChoice[i].getY()))) <
						gearChoice[i].getRadius() && 
						mx<800 && mx>0 && 
						my<600 && my>0 &&
						gearInstalled[i] == 0)
					{
						gearChoice[i].setPosition(mx, my, 0);
						gearClicked = i;	// changes by Chun Fan
						break;
					}
				}
			}
			else // changes by Chun Fan
			{
				gearChoice[gearClicked].setPosition(mx, my, 0);
			}
		}
		// changes by Chun Fan
		else if(mouseEvent == FSMOUSEEVENT_LBUTTONUP)
		{
			// changes by Chun Fan
			if (gearClicked!=-1)
			{
				for (int j=0; j<nGear; j++)
				{
					if ( missingGear[j]==1 && 
						( sqrt((allGear[j].getX()-gearChoice[gearClicked].getX())*
						(allGear[j].getX()-gearChoice[gearClicked].getX()) +
						(allGear[j].getY()-gearChoice[gearClicked].getY())*
						(allGear[j].getY()-gearChoice[gearClicked].getY())) < 10 )
						)
					{
						//printf("Snapped!\n");
						gearChoice[gearClicked].setPosition(allGear[j].getX(), 
							allGear[j].getY(), 0);
						gearInstalled[gearClicked] = 1;
						gearClicked = -1; // changes by Chun Fan
						break;
					}
				}
				gearClicked = -1; // changes by Chun Fan
			}
			/*for (int i=0; i<nChoice; i++)
			{
				for (int j=0; j<nGear; j++)
				{
					if ( missingGear[j]==1 && 
						( sqrt((allGear[j].getX()-gearChoice[i].getX())*
						(allGear[j].getX()-gearChoice[i].getX()) +
						(allGear[j].getY()-gearChoice[i].getY())*
						(allGear[j].getY()-gearChoice[i].getY())) < 10 )
						)
					{
						// changes by Chun Fan
						//printf("Snapped!\n");
						gearChoice[i].setPosition(allGear[j].getX(), 
							allGear[j].getY(), 0);
						gearInstalled[i] = 1;
						break;
					}
				}
			}*/
		}
		
		nInstalled = 0;
		for (int i=0; i<nChoice; i++)
		{
			nInstalled += gearInstalled[i];
		}
		if (nInstalled == nChoice)
			answered = 1;
	}
}

void question::checkAnswer()
{
	if (answered == 1)
	{
		int nMissing = 0;
		for (int i=0; i<nGear; i++)
		{
			if (missingGear[i] == 1)
			{
				for (int j=0; j<nChoice; j++)
				{
					if (allGear[i].getX() == gearChoice[j].getX() &&
						allGear[i].getY() == gearChoice[j].getY() && 
						allGear[i].getN() == gearChoice[j].getN() &&
						allGear[i].getRadius() == gearChoice[j].getRadius() 
						)
						missingGear[i] = 0;
				}
			}
			nMissing += missingGear[i];
			//printf("Gear %d Missing? %s\n", i, missingGear[i]?"Yes":"No");
		}
		if (nMissing == 0)
		{
			correct = 1;
			
			//printf("Correct!\n");
		}
		else
		{
			correct = 0;
			//printf("Wrong!\n");
		}
	}
}

int question::getResults() const
{
	return correct;
}

int question::getAnswered() const
{
	return answered;
} 

void question::calculateSpeed()
{
	for (int i=0; i<nGear; i++)
	{
		if (i==0)
			allGear[i].setSpeed(inputSpeed);
		else 
		{
			if (gearTrain[i]<0)
			{
				allGear[i].setSpeed(-allGear[-gearTrain[i]-1].getSpeed()*
					allGear[-gearTrain[i]-1].getN()/allGear[i].getN());
				/*printf("Gear %d is connected to %d, Speed: %lf\n", i, -gearTrain[i], 
					-allGear[-gearTrain[i]-1].getSpeed()*
					allGear[-gearTrain[i]-1].getN()/allGear[i].getN());*/
			}
			else
			{
				allGear[i].setSpeed(allGear[gearTrain[i]-1].getSpeed());
				/*printf("Gear %d is connected to %d, Speed: %lf\n", i, gearTrain[i], 
					allGear[gearTrain[i]-1].getSpeed());*/
			}
		}
	}
}

void question::animateGears(double dt)
{
	if (correct)
	{
		for (int i=0; i<nGear; i++)
		{
			allGear[i].rotate(dt);
		}
	}
}


