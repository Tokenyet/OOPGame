#ifndef ARCHER_H
#define ARCHER_H
#include "StdAfx.h"
#include "Human.h"

class Archer : public Human
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
	void leftAnimation();
	void rightMoving();
	void rightAnimation();
	void upMoving();
	void upAnimation();
	void downMoving();
	void downAnimation();
	void attackMoving();
	void attackAnimation();
public:
	Archer();
	void OnMove();
	void OnShow();
	void LoadBitmap();
	bool GetAttacking();
	bool GetRestartGame();
	string WhatMyPoisition();
};
#endif