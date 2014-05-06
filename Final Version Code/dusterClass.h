#ifndef YYDUSTERCLASS_H_IS_INCLUDED
#define YYDUSTERCLASS_H_IS_INCLUDED

#include "yspng.h"

class DusterClass
{
private:
	int state;
	YsRawPngDecoder png;
	int x;
	int y;
	int life;

	void CleanUp(void);

public:
	DusterClass(void);
	~DusterClass(void);

	void Initialize(void);
	bool IsDusterClicked(const int mx, const int my, const int lb) const;
	void Display(void) const;
	void SetState(bool state);
	bool GetState(void) const;
	bool TimeOut(const int duster_startTime, const int timeNow) const;
};

#endif
