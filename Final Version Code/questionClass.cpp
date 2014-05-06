#include <stdio.h>
#include <string.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "textInput.h"
#include "questionClass.h"


QuestionClass::QuestionClass(void)
{
	Initialize();
}

void QuestionClass::Initialize(void)
{
	qn = NULL;
	ans = NULL;
}

QuestionClass::~QuestionClass(void)
{
	CleanUp();
}

void QuestionClass::CleanUp()
{
	if (qn!=NULL)
	{
		qn = NULL;
	}
	if (ans!=NULL)
	{
		ans = NULL;
	}
}

void QuestionClass::Set(const char question[], const char answer[])
{
	qn = question;
	ans = answer;
}

void QuestionClass::CopyStringSection(const int startIndex, const int endIndex, const char from[], char to[])
{
	for (int j=startIndex+1; j<endIndex; j++)
	{
		to[j-startIndex-1] = from[j];
	}
	to[endIndex-startIndex-1] = 0;
}

void QuestionClass::PrintQn(void) 
{
	if (qn!=NULL)
	{
		glColor3ub(255,255,255);
		int length = strlen(qn);
	
		if (length > 20)
		{
			char str[256];
			str[255] = 0;

			int startOfLineIndex = 0;
			int endOfLineIndex = 0;
		
			for (int i=0; (i<length && i<255); i++)
			{
				char c = qn[i];

				if ((i!=0) && (i%20!=0))
				{
					if ((c<='/') || ((c>=':') && (c<='@')) || ((c>='[') && (c<='`')) || (c>='{'))
					{
						endOfLineIndex = i;
					}
				}
				else if ((i!=0) && (i%20==0))
				{
					if (startOfLineIndex == 0)
					{
						startOfLineIndex = -1;
					}
					
					CopyStringSection(startOfLineIndex, endOfLineIndex, qn, str);
					startOfLineIndex = endOfLineIndex;

					glRasterPos2d(50, 100 + (i/20)*50);
					YsGlDrawFontBitmap20x32(str);
				}
				if ((i==254) || (i==length-1))
				{
					CopyStringSection(startOfLineIndex, length, qn, str);
				
					glRasterPos2d(50, 100 + ((i/20) + 1)*50);
					YsGlDrawFontBitmap20x32(str);
					break;
				}
			}
		}		
		else
		{
			glRasterPos2d(50, 100);
			YsGlDrawFontBitmap20x32(qn);
		}
	}
	else
	{
		printf("*qn of QuestionClass is NULL.\n");
	}
}

bool QuestionClass::CheckAnswer(const char *answer)
{
	if (answer!=NULL)
	{
		char ansString[256];
		strncpy(ansString, answer, 255);
		ansString[255] = 0;

		for (int i=0; ansString[i]!=0; i++)
		{
			ansString[i] = toupper(ansString[i]);
		}

		if (strcmp(ansString, ans) != 0)
		{

			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		printf("*ans of QuestionClass is NULL.\n");
		return 0;
	}
}

const char* QuestionClass::GetAnswer(void)
{
	return ans;
}
