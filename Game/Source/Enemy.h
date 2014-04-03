#ifndef ENEMY_H
#define ENEMY_H

#include "Human.h"
#include "Ewalk.h"
#include "EGravity.h"

class Enemy : public Human
{
private :
	Ewalk *walk_Behavior;
	EGravity *myGravity_Behavior;
	double interval_time;
	double timeNow,timePast;
	double timeRestriction;
	void resetTimeParameter(bool JumpOrFall);
	void walking_nearby();
	/*double timeUpLimit;
	void jumpUptimeParameter();
	bool isOnGround,isOnSky,isKeepUpMove;
	bool dojump();*/
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