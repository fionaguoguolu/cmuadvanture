#include "gearGame.h"

gearGame::gearGame()
{
	nQuestion = 0;
	gearQuestion = NULL;
	questionCaption = NULL;
	nTeeth = NULL;
	x = NULL; 
	y = NULL; 
	theta = NULL;
	relation = NULL;
	// changes by Chun Fan
	if(YSOK==png.Decode("GearBackground.png"))
    {
        //printf("Read Width=%d Height=%d\n",png.wid,png.hei);
        png.Flip();
    }
    else
    {
        printf("Read Error!\n");
        return ;
    }
}

gearGame::~gearGame()
{
	cleanup();	
}

int gearGame::read(char fstr[])
{
	char str[256];	
	
	if (file.open(fstr, "r") && fgets(str,255,file.getFp())!=NULL)
	{
		nQuestion = atoi(str);
		// changes by Chun Fan
		//printf("Read number of Questions: %d\n", nQuestion);
		gearQuestion = new question[nQuestion];
		questionCaption = new char*[nQuestion];
		if (gearQuestion != NULL & questionCaption != NULL)
		{
			// changes by Chun Fan
			//printf("Succesfully allocate memory to gearQuestion\n");
			int nReadQuestion=0;
			
			while(fgets(str,255,file.getFp())!=NULL && nReadQuestion<nQuestion)
			{	
				questionCaption[nReadQuestion] = new char[strlen(str)+1];
				strcpy(questionCaption[nReadQuestion],str);
				
				int nGear = 0;
				double inputSpeed = 0;
				
				if (fgets(str,255,file.getFp())!=NULL)
				{			
					strParser.SetStringAndParse(str);
					// changes by Chun Fan
					//printf("\nnGear & inputSpeed: %s", str);
					if (strParser.GetNumWords()==2)
					{
						char word[256];						
						strParser.GetWord(word,255,0);
						nGear = atoi(word);
						strParser.GetWord(word,255,1);
						inputSpeed = atoi(word);
						
						// changes by Chun Fan
						//printf("nGear: %d & inputSpeed: %lf\n", nGear, inputSpeed);
						//printf("Succesfully read question %d\n",nReadQuestion);
						
						nTeeth = new int[nGear];
						if (nTeeth == NULL)
							return 0;
						
						x = new double[nGear]; 
						if (x == NULL)
							return 0;
							
						y = new double[nGear]; 
						if (y == NULL)
							return 0;

						theta = new double[nGear];
						if (theta == NULL)
							return 0;
							
						relation = new int[nGear];
						if (relation == NULL)
							return 0;
						
						// changes by Chun Fan
						//printf("Succesfully allocate memory to nTeeth, x, y, theta & relation\n");
					}
					else
					{	
						printf("Error in reading number of gear & input speed.\n");
						return 0;
					}
				}
				else
				{
					printf("Error: invalid nGear or input speed for question %d!\n", nReadQuestion);
					return 0;
				}
				
				int nReadGear = 0;
				
				while(nReadGear<nGear)
				{
					if (fgets(str,255,file.getFp())!=NULL)
					{
						strParser.SetStringAndParse(str);
						if (strParser.GetNumWords()==5)
						{
							char word[256];						
							strParser.GetWord(word,255,0);
							nTeeth[nReadGear] = atoi(word);
							strParser.GetWord(word,255,1);
							x[nReadGear] = atof(word);
							strParser.GetWord(word,255,2);
							y[nReadGear] = atof(word);
							strParser.GetWord(word,255,3);
							theta[nReadGear] = atof(word);
							strParser.GetWord(word,255,4);
							relation[nReadGear] = atoi(word);
							
							// changes by Chun Fan
							//printf("Succesfully read gear %d\n",nReadGear);
							//printf("%d\t%lf\t%lf\t%lf\t%d\n",nTeeth[nReadGear],
							//	x[nReadGear], y[nReadGear], theta[nReadGear],
							//	relation[nReadGear]);
							nReadGear++;
						}
						else 
						{
							printf("Error: invalid gear specification for gear %d in question %d!\n", nReadGear, nReadQuestion);
							//cleanup();
							partialCleanup();
							return 0;
						}
					}
					else 
					{
						printf("Error: cannot read gear %d input for question %d!\n", nReadGear, nReadQuestion);	
						partialCleanup();
						return 0;
					}
				}
				// changes by Chun Fan
				//printf("Input speed: %lf\n", inputSpeed);
				gearQuestion[nReadQuestion].createGear(nGear, inputSpeed, 
					nTeeth, x, y, theta, relation);
					
				nReadQuestion++;
				partialCleanup();
				
			}
			file.close();
			return 1;
		}	
		else
		{
			printf("Fail to allocate memory!\n");
			return 0;
		}
	}
	else
		printf("Fail to open file!\n");
	
	return 0;
}

int gearGame::run()
{	
	int winWidNew = 800;
	int winHeiNew = 600;

	FsGetWindowSize(winWidNew,winHeiNew);
	glViewport(0,0,winWidNew,winHeiNew);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,(float)winWidNew-1,(float)winHeiNew-1,0,-1,1);
	
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	displayBackground(); // changes by Chun Fan
	displayInstruction();
	
	FsClearEventQueue();
	
	FsPollDevice();
	int key = FsInkey();
	while (key!=FSKEY_ENTER)
	{
		FsPollDevice();
		key = FsInkey();

		if (key == FSKEY_ESC)
			return 0;
		FsSleep(10);
	}	
	
	int retake=1;	
	while (retake)
	{
		cleanup();
		// changes by Chun Fan
		if (!read("gear.txt"))		
		{
			printf("Fail to load gear game question!\n");
			return -1;
		}
		/*if (read("gear.txt"))		
		{			
			printf("Read file!\n");
		}
		else
		{
			printf("Fail to load gear game question!\n");
			return -1;
		}*/
		
		retake = 0;
		for (int i=0; i<nQuestion; i++)
		{
			gearQuestion[i].calculateSpeed();
		
			gearQuestion[i].prepareQuestion();
			
			int key=FSKEY_NULL;
			double dt = 0;
		
			int counter = 0;
			
			FsPassedTime();
			while(1)
			{
				FsPollDevice();
				//key=FsInkey();
				gearQuestion[i].getUserInput();
				gearQuestion[i].checkAnswer();			
				
				FsGetWindowSize(winWidNew,winHeiNew);
				glViewport(0,0,winWidNew,winHeiNew);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0,(float)winWidNew-1,(float)winHeiNew-1,0,-1,1);

				glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
				
				dt = FsPassedTime()/1000.0;
				//printf("dt = %lf\n", dt);
				gearQuestion[i].animateGears(dt);
				
				// think about the precedence of gear! 	
				displayBackground(); // changes by Chun Fan
				gearQuestion[i].displayQuestion();	
				displayQuestionNumber(i+1);
				
				FsSwapBuffers();
				FsSleep(5);
				
				if (gearQuestion[i].getAnswered())
				{
					counter++;
					if (counter >= 250)
						break;
				}
			}
		}
		
		FsClearEventQueue();
		
		FsGetWindowSize(winWidNew,winHeiNew);
		glViewport(0,0,winWidNew,winHeiNew);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)winWidNew-1,(float)winHeiNew-1,0,-1,1);

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		displayBackground(); // changes by Chun Fan
		retake = displayScores();
		// changes by Chun Fan
		//printf("retake: %d\n", retake);
	}
	
	int score=getScore();
	if (score > 0.5*nQuestion)
		return 1; //passed
	else
		return 0; //failed
}

void gearGame::displayQuestionNumber(int QuestionNumber)
{
	char str[256];
	glColor3ub(0, 0, 0);
	glRasterPos2d(250, 50);	
	sprintf(str, "Question %d:", QuestionNumber);
	YsGlDrawFontBitmap16x24(str);
	
	// display caption:
	glColor3ub(0, 0, 0);
	glRasterPos2d(250, 50+25);	
	YsGlDrawFontBitmap12x16(questionCaption[QuestionNumber-1]);
}

void gearGame::displayInstruction()
{
	int startX, startY;	
	glColor3ub(0,0,0);
	glRasterPos2d(25, 55);
	YsGlDrawFontBitmap20x32("Welcome to Machine Mechanic Class!");
	startX = 25;
	startY = 65+30;
	glColor3ub(0,0,255);
	glRasterPos2d(startX, startY);
	YsGlDrawFontBitmap16x20("You are going to learn Gears today.");
	glRasterPos2d(startX, startY+25);
	YsGlDrawFontBitmap16x20("One of its usage is to change speed.");
	glRasterPos2d(startX, startY+50);
	YsGlDrawFontBitmap16x20("Connecting gears forms a gear train.");
	glRasterPos2d(startX, startY+75);
	YsGlDrawFontBitmap16x20("The speed changes according to the gear ratio:");
	glColor3ub(255,0,0);
	startX = 400;
	startY = 300;
	glRasterPos2d(startX, startY);
	YsGlDrawFontBitmap16x24("Instruction:");
	startX += 5;
	startY += 30;
	glRasterPos2d(startX, startY);
	YsGlDrawFontBitmap12x16("The gear train is not working!");
	glRasterPos2d(startX, startY+25);
	YsGlDrawFontBitmap12x16("Fill in the missing gears!");
	glRasterPos2d(startX, startY+50);
	YsGlDrawFontBitmap12x16("Just drag and drop!");
	glRasterPos2d(startX, startY+75);
	YsGlDrawFontBitmap12x16("You only have one chance!");
	glRasterPos2d(startX, startY+100);
	YsGlDrawFontBitmap12x16("Think before you leap!");
	glColor3ub(0,0,255);
	glRasterPos2d(25, 520);
	YsGlDrawFontBitmap20x32("Are you ready? Press ENTER to start!");
	glColor3ub(255,0,0);
	glRasterPos2d(25, 520+50);
	YsGlDrawFontBitmap20x32("Are you scared? Press ESC to return!");
	
	
	YsRawPngDecoder png;
	
	// Display print screen!
	if (YSOK == png.Decode("GearGameInterface.png"))
	{
		// changes by Chun Fan
		//printf("Pic width:%d\tPic height: %d\n", png.wid, png.hei);
		png.Flip();
		glRasterPos2d(100,475);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
	}
	else
	{
		printf("Failed to loading picture GearGameInterface!\n");
	}

	// Display equation!	
	if (YSOK == png.Decode("GearRatioEquation.png"))
	{
		// changes by Chun Fan
		//printf("Pic width:%d\tPic height: %d\n", png.wid, png.hei);
		png.Flip();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2d(375-png.wid/2,217+png.hei/2);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}
	else
	{
		printf("Failed to loading picture GearRatioEquation!\n");
	}
	
	FsSwapBuffers();
	
}

int gearGame::getScore()
{
	int score=0;
	for (int i=0; i<nQuestion; i++)
	{	
		score += gearQuestion[i].getResults();
	}
	return score;
}

int gearGame::displayScores()
{
	int total_score=getScore();
	
	char str[256];
	glColor3ub(0,0,0);
	glRasterPos2d(80, 295); // changes by Chun Fan
	sprintf(str, "You scored %d out of %d questions.", total_score, nQuestion);
	YsGlDrawFontBitmap20x32(str);
	
	if (total_score > 0.5*nQuestion)
	{
		// you passed!
		glColor3ub(0,0,255);
		glRasterPos2d(40, 305+32);
		YsGlDrawFontBitmap20x32("Good job! You have passed the class!");
		glColor3ub(0,0,255);
		glRasterPos2d(80, 520);// changes by Chun Fan
		YsGlDrawFontBitmap20x28("Try again? Press ENTER to start!");
		glColor3ub(255,0,0);
		glRasterPos2d(80, 520+50); // changes by Chun Fan
		YsGlDrawFontBitmap20x28("Tired? Press other keys to exit!");
	}
	else
	{
		// you failed!
		glColor3ub(255,0,0);
		glRasterPos2d(40, 305+32);
		YsGlDrawFontBitmap20x32("You failed the class! Please retake!");
		glColor3ub(0,0,255);
		glRasterPos2d(80, 520); // changes by Chun Fan	
		YsGlDrawFontBitmap20x28("Try again? Press ENTER to start!");
		glColor3ub(255,0,0);
		glRasterPos2d(50, 520+50); // changes by Chun Fan
		YsGlDrawFontBitmap20x28("Given up? Press other keys to exit!");
	}
	
	FsSwapBuffers();
	
	FsPollDevice();
	int key = FsInkey();
	while (key==NULL)
	{
		FsPollDevice();
		key = FsInkey();
		FsSleep(10);
	}
	switch (key)
	{
		case FSKEY_ENTER:
			return 1;
		default:
			return 0;
	}
	
}

void gearGame::cleanup()
{
	if (gearQuestion!=NULL)
	{
		delete [] gearQuestion;
		gearQuestion = NULL;
	}
	
	if (nQuestion != 0 && questionCaption != NULL)
	{
		for (int i=0; i<nQuestion; i++)
		{
			if (questionCaption[i]=NULL)
			{
				delete questionCaption[i];
				questionCaption[i] = NULL;
			}
		}
		delete [] questionCaption;
		questionCaption = NULL;
	}

	nQuestion = 0;
	
	if (nTeeth!=NULL)
	{
		delete [] nTeeth;
		nTeeth = NULL;
	}
	
	if (x!=NULL)
	{
		delete [] x;
		x = NULL;
	}
	
	if (y!=NULL)
	{
		delete [] y;
		y = NULL;
	}
	
	if (theta!=NULL)
	{
		delete [] theta;
		theta = NULL;
	}
	
	if (relation!=NULL)
	{
		delete [] relation;
		relation = NULL;
	}
}

void gearGame::partialCleanup()
{
	if (nTeeth!=NULL)
	{
		delete [] nTeeth;
		nTeeth = NULL;
	}
	
	if (x!=NULL)
	{
		delete [] x;
		x = NULL;
	}
	
	if (y!=NULL)
	{
		delete [] y;
		y = NULL;
	}
	
	if (theta!=NULL)
	{
		delete [] theta;
		theta = NULL;
	}
	
	if (relation!=NULL)
	{
		delete [] relation;
		relation = NULL;
	}
}

// changes by Chun Fan
void gearGame::displayBackground()
{
	int winWid,winHei;
	FsGetWindowSize(winWid, winHei);
	glRasterPos2d(0.0, (double)(winHei-1));
	glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
}