#include "StdAfx.h"
#include "EGravity.h"


void Normal_Gravity::Dropping(int &y,bool &d_Restrict,int d_restric_y,
	double &timeNow,double &timePast,double interval_time,int heigth)
{
		timeNow+= interval_time;
		int deltaY = gravity(0,4.4,timeNow,timePast);
		if(deltaY < -10)
			deltaY = -10;
		if(d_Restrict)
		{
			if(!(y + heigth >= d_restric_y))
			{
				y -= deltaY;
			}
			if((y + heigth >= d_restric_y))
			{
				y = d_restric_y - heigth;
				resetTimeParameter(timeNow,timePast);
				isOnGround = true;
			}
		}
		else
		{
				y -= deltaY;
				isOnGround = false;
		}
		timePast = timeNow;
}


int Normal_Gravity::gravity(double Vo,double g,double Time,double PriTime)
{
	double delta_t = Time-PriTime;
    int GravityX = 0;
    GravityX = (int)((Vo * delta_t) - (g / 2) *((Time * Time)-(PriTime*PriTime)));
    return GravityX;
}

void Normal_Gravity::resetTimeParameter(double &timeNow,double &timePast)
{
	timeNow = timePast  = 0;
}

void Normal_Gravity::JumpOrFall(int&y,bool &u_Restrict,bool &d_Restrict
		,int u_y,int d_y,double &time_restriction,double &timeNow
		,double &timePast,double interval_time,int heigth,bool canJump)
{
	Dropping(y,d_Restrict,d_y,timeNow,timePast,interval_time,heigth);
}