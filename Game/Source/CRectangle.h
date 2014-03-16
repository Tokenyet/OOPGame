#ifndef CRECTANGLE_H
#define CRECTANGLE_H
#include "stdafx.h"

class CRectangle
{
private:
	int x_Left ;
	int y_Left ;
	int x_Right ;
	int y_Right ;
public:
	CRectangle();
	~CRectangle();
	void SetRectangle(int Lx,int Ly,int Rx,int Ry);
	bool Intersect(CRectangle);
	int Get_Lx();
	int Get_Ly();
	int Get_Rx();
	int Get_Ry();
};
#endif