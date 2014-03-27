#ifndef CHARCTER_H
#define CHARCTER_H
#include "StdAfx.h"
#include "Human.h"

class Charcter : public Human
{
private :
	double falling_speed,timeNow,timePast,g;
	void resetJumping(bool JumpOrFall);
	int gravity(double Vo,double g,double Time,double PriTime);
protected:
	void leftMoving();
	void rightMoving();
	void upMoving();
	void downMoving();
public:
	Charcter();
	void OnMove();
	void OnShow();
	void LoadBitmap();
};
#endif