#ifndef AWARDSTAGE_IS_INCLUDED
#define AWARDSTAGE_IS_INCLUDED

#include "yspng.h"

class AwardStage
{
private:
	YsRawPngDecoder stage;
	char *dept;
	int winHei, winWid;
public:
	AwardStage(void);

	void SetDept(char *input);
	void DrawStage(void);
	void PrintCert(void);
};

#endif