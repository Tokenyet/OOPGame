#ifndef BOUNDING_OBS_H
#define BOUNDING_OBS_H
#include "CRectangle.h"


class Bounding_Obs
{
private:
	CRectangle rowRect,colRect,originRect;
public:
	Bounding_Obs();
	~Bounding_Obs();
	void SetOriginRectangle(int lx,int ly,int width,int height,int detect_range);
	bool RightIntersect(CRectangle);
	bool LeftIntersect(CRectangle);
	bool UpIntersect(CRectangle);
	bool DownIntersect(CRectangle);
	CRectangle GetRowRect();
	CRectangle GetColRect();
	CRectangle GetOriginRect();
	int GetWidth();
	int GetHeight();
};



#endif