#ifndef YYDISTRACTIONCLASS_H_IS_INCLUDED
#define YYDISTRACTIONCLASS_H_IS_INCLUDED

#include "yspng.h"

class DistractionClass
{
private:
	int state;
	YsRawPngDecoder png;
	int x;
	int y;
	int life;
	int timeStarted;
	
	void Initialize(void);
	void CleanUp(void);

public:
	DistractionClass(void);
	~DistractionClass(void);

	void Reset(char *input);
	bool IsDistractionClicked(const int mx, const int my, const int lb) const;
	void Display(void) const;
	void SetState(bool state);
	bool GetState(void) const;
	bool TimeOut(const int time) const;
};

#endif
