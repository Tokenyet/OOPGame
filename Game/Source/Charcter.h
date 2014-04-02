#ifndef CHARCTER_H
#define CHARCTER_H
#include "StdAfx.h"
#include "Human.h"

class Charcter : public Human
{
private :
	double interval_time;
	double timeUpLimit;
	double timeNow,timePast;
	void resetTimeParameter(bool JumpOrFall);
	int gravity(double Vo,double g,double Time,double PriTime);
	void jumpUptimeParameter();
	bool isOnGround,isOnSky,isKeepUpMove;
	bool dojump();
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