#ifndef ENEMY_H
#define ENEMY_H

#include "Human.h"

class Enemy : public Human
{
private :
	double interval_time;
	double timeNow,timePast;
	void resetTimeParameter(bool JumpOrFall);
	void walking_nearby();
	bool isOnGround;
	/*double timeUpLimit;
	void jumpUptimeParameter();
	bool isOnGround,isOnSky,isKeepUpMove;
	bool dojump();*/
	int gravity(double Vo,double g,double Time,double PriTime);
/*protected:
	void leftMoving();
	void rightMoving();
	void upMoving();*/
	void downMoving();
public:
	Enemy(int,int);
	void OnMove();
	void OnShow();
	void LoadBitmap();
};

#endif