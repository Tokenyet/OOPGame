#include "StdAfx.h"
#include "Gravity.h"
#include "Charcter.h"
#include "audio.h"

	Gravity::Gravity(int *value_jump_y)
	{
		sync_y = value_jump_y;
		isOnGround = false;
		isOnSky = false;
		isKeepUpMove = false;
		interval_time = 0.5f;
		resetTimeParameter(true);
		soundOn = false; 
		//g = 10;
	}
	Gravity::~Gravity()
	{
		//delete sync_y;
	}

	void Gravity::Jumping()
	{
		int *y = sync_y;
		jumpUptimeParameter(trigger_upMove);
		//int speed = 5;
		int deltaY = gravity(30,4.4,timeNow,timePast);
		if(deltaY < 0)
			deltaY = 0;

		if(isOnSky&&!isOnGround)
			*y -= deltaY;//Vo(£Gt1-£Gt2) - 1/2g[(£Gt1)^2-(£Gt2)^2]

		timePast = timeNow;
	/*		else
				y -= speed;*/
	}
	void Gravity::Falling()
	{
		int *y = sync_y;
		timeNow+= interval_time;
		int speed = 5;
		int deltaY = gravity(0,4.4,timeNow,timePast);
		if(deltaY < -10)
			deltaY = -10;
		//int height = picture_animation->Height();
			if(!isOnGround)
				*y -= deltaY;
		timePast = timeNow;
	}

	void Gravity::jumpUptimeParameter(bool upMove)
	{
		if(timeUpLimit > interval_time * 15)
			timeUpLimit = interval_time * 15;
		if(timeNow <= timeUpLimit)
		{
			if(isKeepUpMove)
			timeUpLimit += interval_time;//keeptime = interval time
			if(!upMove)
				isKeepUpMove = false;
			timeNow += interval_time;
		}
		else
		{
			resetTimeParameter(true);
			isOnSky = false;
		}
	}
	void Gravity::resetTimeParameter(bool JumpOrFall)
	{
		timeNow = timePast  = 0;
		timeUpLimit = interval_time * 10;
	}
	int Gravity::gravity(double Vo,double g,double Time,double PriTime)
    {
		double delta_t = Time-PriTime;
        int GravityX = 0;
        GravityX = (int)((Vo * delta_t) - (g / 2) *((Time * Time)-(PriTime*PriTime)));
        return GravityX;
    }
	bool Gravity::Dojump(bool upMove)
	{
		this->trigger_upMove = upMove;
		if(isOnGround&&upMove)
		{
			if(soundOn)
			{
				game_framework::CAudio::Instance()->Play(1,true);
				game_framework::CAudio::Instance()->Play(1,false);
			}
			isOnGround = false;
			isOnSky = true;
			isKeepUpMove = true;
			return true;
		}
		if(isOnSky)
			return true;
		return false;
	}


	bool Gravity::GetOnGround(){return isOnGround;}
	bool Gravity::GetOnSky(){return isOnSky;}
	bool Gravity::GetKeepUpMove(){return isKeepUpMove;}

	void Gravity::SetOnGround(bool onGround)
	{
		isOnGround = onGround;
		if(onGround)
		resetTimeParameter(true);
	}
	void Gravity::SetOnSky(bool onSky)
	{
		isOnSky = onSky;
	}
	void Gravity::SetKeepUpMove(bool keepUpMove)
	{
		isKeepUpMove = keepUpMove;
	}
	void Gravity::SetSound(bool OnOff)
	{
		soundOn = OnOff;
	}