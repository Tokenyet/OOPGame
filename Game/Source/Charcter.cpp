#include "StdAfx.h"
#include "Charcter.h"
#include "audio.h"

	Charcter::Charcter():Human(SIZE_X/2-50,0)
	{
		head_Direction = Head_Right;
		upMove = downMove = rightMove = leftMove = false;
		upRestriction=downRestriction=rightRestriction=leftRestriction = false;
		isOnGround = false;
		isOnSky = false;
		isKeepUpMove = false;
		interval_time = 0.5f;
		resetTimeParameter(true);
		//g = 10;
	}
	void Charcter::OnMove()
	{
		if (leftMove)
			leftMoving();
		if (rightMove)
			rightMoving();
		if (dojump())
			upMoving();
		if (!isOnSky)
			downMoving();
		if(!leftMove&&!rightMove&&!upMove&&!downMove)
			picture_animation.Reset();
		myRect.SetOriginRectangle(SIZE_X/2-50,GetY(),picture_animation.Width(),picture_animation.Height(),5);//SIZE_X/2-50
	}
	void Charcter::LoadBitmap()
	{
		char *RWalking[2] = {"Bitmaps/r_stand.bmp","Bitmaps/r_run.bmp"};
		char *LWalking[2] = {"Bitmaps/l_stand.bmp","Bitmaps/l_run.bmp"};
		char *RJumping[3] = {"Bitmaps/r_jump-1.bmp","Bitmaps/r_jump-2.bmp","Bitmaps/r_jump-3.bmp"};
		char *LJumping[3] = {"Bitmaps/l_jump-1.bmp","Bitmaps/l_jump-2.bmp","Bitmaps/l_jump-3.bmp"};

		picture_animation.LoadAnimation(R_Walking,RWalking,2);
		picture_animation.LoadAnimation(L_Walking,LWalking,2);
		picture_animation.LoadAnimation(R_Jumping,RJumping,3);
		picture_animation.LoadAnimation(L_Jumping,LJumping,3);
		picture_animation.StateInitialize();
		picture_animation.SetTopLeft(GetX(),GetY());
	}
	void Charcter::OnShow()
	{
		picture_animation.SetTopLeft(SIZE_X/2-50,GetY());//SIZE_X/2-50
		picture_animation.OnShow();
	}
	void Charcter::leftMoving()
	{
		rightRestriction = false;
		int speed = 5;
		if(getLeftRestriction())
		{
			if(!(SIZE_X/2-50 <= leftBoundedValue)) // SIZE_X/2-50 <= leftBoundedValue
				GetX() -= 5;
		}
		else
			GetX()-=5;

		if(!rightMove)
		{
			head_Direction = Head_Left;
			picture_animation.OnMove(L_Walking);
		}

			/*else
				x -= speed;*/
	}
	void Charcter::rightMoving()
	{

		int speed = 5;
		int width = picture_animation.Width();
		if(getRightRestriction())
		{
			if(!(SIZE_X/2-50 + width>= rightBoundedValue))//SIZE_X/2-50 + width >= rightBoundedValue
				GetX() += speed;
		}
		else
			GetX()+= speed;
		if(!leftMove)
		{
			head_Direction = Head_Right;
			picture_animation.OnMove(R_Walking);
		}

			/*else
				x += speed;*/
	}
	void Charcter::upMoving()
	{
		if(head_Direction == Head_Left)
			picture_animation.OnMove(L_Jumping);
		if(head_Direction == Head_Right)
			picture_animation.OnMove(R_Jumping);
		jumpUptimeParameter();
		//int speed = 5;
		int deltaY = gravity(30,4.4,timeNow,timePast);
		if(deltaY < 0)
			deltaY = 0;
		/*if(deltaY < -10)
			deltaY = -10;
		if(deltaY > 10)
			deltaY = 10;*/
		if(getUpRestriction())
		{
			if(!(GetY() <= upBoundedValue))
				GetY()-= deltaY;
			if(GetY() <= upBoundedValue)
			{
				isOnSky = false;
				isKeepUpMove = false;
			}
		}
		else
		{
			GetY()-= deltaY;//Vo(£Gt1-£Gt2) - 1/2g[(£Gt1)^2-(£Gt2)^2]
			//Vo(£Gt1-£Gt2) - 1/2g[(£Gt1)^2-(£Gt2)^2]
		}
		timePast = timeNow;
	/*		else
				y -= speed;*/
	}
	void Charcter::downMoving()
	{
		if(!isOnGround)
		{
			if(head_Direction == Head_Left)
				picture_animation.OnMove(L_Jumping);
			if(head_Direction == Head_Right)
				picture_animation.OnMove(R_Jumping);
		}
		else
			if(head_Direction == Head_Left&&isOnGround)
				picture_animation.OnMove(L_Walking);
			if(head_Direction == Head_Right&&isOnGround)
				picture_animation.OnMove(R_Walking);

		timeNow+= interval_time;
		int speed = 5;
		int deltaY = gravity(0,4.4,timeNow,timePast);
		if(deltaY < -10)
			deltaY = -10;
		int height = picture_animation.Height();
		if(getDownRestriction())
		{
			if(!(GetY() + height >= downBoundedValue))
			{
				GetY() -= deltaY;
				isOnGround = false;
			}
			if((GetY() + height >= downBoundedValue))
			{
				GetY() = downBoundedValue - height;
				resetTimeParameter(true);
				isOnGround = true;
			}
		}
		else
		{
				GetY() -= deltaY;
				isOnGround = false;
		}
		timePast = timeNow;
	}

	void Charcter::jumpUptimeParameter()
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
	void Charcter::resetTimeParameter(bool JumpOrFall)
	{
		timeNow = timePast  = 0;
		timeUpLimit = interval_time * 10;
	}
	int Charcter::gravity(double Vo,double g,double Time,double PriTime)
    {
		double delta_t = Time-PriTime;
        int GravityX = 0;
        GravityX = (int)((Vo * delta_t) - (g / 2) *((Time * Time)-(PriTime*PriTime)));
        return GravityX;
    }
	bool Charcter::dojump()
	{
		if(isOnGround&&upMove)
		{
			game_framework::CAudio::Instance()->Play(1,true);
			game_framework::CAudio::Instance()->Play(1,false);
			isOnGround = false;
			isOnSky = true;
			isKeepUpMove = true;
			return true;
		}
		if(isOnSky)
			return true;
		return false;
	}