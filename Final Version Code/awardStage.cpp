#include <stdio.h>
#include <string.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "awardStage.h"

AwardStage::AwardStage(void)
{
	winHei = 600;
	winWid = 800;

	if(stage.Decode("awardStage.png"))
    {
        stage.Flip();
    }
    else
    {
        printf("Error loading stage png.\n");
    }	
}

void AwardStage::SetDept(char *input)
{
	dept = input;
}

void AwardStage::DrawStage(void)
{
	FsGetWindowSize(winWid, winHei);
	glRasterPos2d(0.0,(double)(winHei-1));
	glDrawPixels(stage.wid,stage.hei,GL_RGBA,GL_UNSIGNED_BYTE,stage.rgba);
}

void AwardStage::PrintCert(void)
{
	char msg[256];
	msg[255] = 0;

	glColor3ub(0, 0, 0);
	
	strcpy(msg, "Congratulations!");
	glRasterPos2d(100, 70);
	YsGlDrawFontBitmap16x24(msg);

	strcpy(msg, "You have graduated from the");
	glRasterPos2d(100, 100);
	YsGlDrawFontBitmap16x24(msg);

	glRasterPos2d(100, 130);
	YsGlDrawFontBitmap16x24(dept);
		
	strcpy(msg, "department!");
	glRasterPos2d(100, 160);
	YsGlDrawFontBitmap16x24(msg);
}