#include "StdAfx.h"
#include "Archer.h"
#include "audio.h"

	Archer::Archer():Human(SIZE_X/2-50,0)
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
	void Archer::OnMove()
	{
		if (leftMove)
		{
			leftMoving();
			leftAnimation();
		}
		if (rightMove)
		{
			rightMoving();
			rightAnimation();
		}
		if (dojump())
		{
			upMoving();
			upAnimation();
		}
		if (!isOnSky)
		{
			downMoving();
			downAnimation();
		}
		if(attackMove)
		{
			attackMoving();
			attackAnimation();
		}
		if(!leftMove&&!rightMove&&!upMove&&!downMove&&!attackMove)
			picture_animation->Reset();
		//myRect.SetOriginRectangle(SIZE_X/2-50,GetY(),picture_animation->Width(),picture_animation->Height(),5);//SIZE_X/2-50
		myRect.SetOriginRectangle(SIZE_X/2-50,GetY(),GetWidth(),GetHeight(),5);
	}
	void Archer::LoadBitmap()
	{
		char *RWalking[2] = {"Bitmaps/R/r_walk-1ar.bmp","Bitmaps/R/r_walk-2ar.bmp"};
		char *LWalking[2] = {"Bitmaps/L/l_walk-1ar.bmp","Bitmaps/L/l_walk-2ar.bmp"};
		char *RJumping[2] = {"Bitmaps/R/r_jump-1ar.bmp","Bitmaps/R/r_jump-2ar.bmp"};
		char *LJumping[2] = {"Bitmaps/L/l_jump-1ar.bmp","Bitmaps/L/l_jump-2ar.bmp"};
		char *RAttack[4] =  {"Bitmaps/R/r_attack-1ar.bmp","Bitmaps/R/r_attack-2ar.bmp","Bitmaps/R/r_attack-3ar.bmp","Bitmaps/R/r_attack-4ar.bmp"};
		char *LAttack[4] =  {"Bitmaps/L/l_attack-1ar.bmp","Bitmaps/L/l_attack-2ar.bmp","Bitmaps/L/l_attack-3ar.bmp","Bitmaps/L/l_attack-4ar.bmp"};

		picture_animation->LoadAnimation(R_Walking,RWalking,2,0);
		picture_animation->LoadAnimation(L_Walking,LWalking,2,0);
		picture_animation->LoadAnimation(R_Jumping,RJumping,2,0);
		picture_animation->LoadAnimation(L_Jumping,LJumping,2,0);
		picture_animation->LoadAnimation(R_Attacking,RAttack,4,0);
		picture_animation->LoadAnimation(L_Attacking,LAttack,4,0);
		picture_animation->StateInitialize();
		setMySize(picture_animation->Width(),picture_animation->Height());
		picture_animation->SetTopLeft(GetX(),GetY());
	}
	void Archer::OnShow()
	{
		picture_animation->SetTopLeft(SIZE_X/2-50,GetY());//SIZE_X/2-50
		picture_animation->OnShow();
	}
	void Archer::leftMoving()
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

			/*else
				x -= speed;*/
	}
	void Archer::rightMoving()
	{

		int speed = 5;
		int width = picture_animation->Width();
		if(getRightRestriction())
		{
			if(!(SIZE_X/2-50 + width>= rightBoundedValue))//SIZE_X/2-50 + width >= rightBoundedValue
				GetX() += speed;
		}
		else
			GetX()+= speed;

			/*else
				x += speed;*/
	}
	void Archer::upMoving()
	{
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
	void Archer::downMoving()
	{
		timeNow+= interval_time;
		int speed = 5;
		int deltaY = gravity(0,4.4,timeNow,timePast);
		if(deltaY < -10)
			deltaY = -10;
		//int height = picture_animation->Height();
		int height = GetHeight();
		if(getDownRestriction())
		{
			if(!(GetY() + height > downBoundedValue))
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
	void Archer::attackMoving()
	{
	}
	void Archer::leftAnimation()
	{	
		bool gothrough = true;
		if(attackMove)
			gothrough = false;
		if(!rightMove&&gothrough)
		{
			head_Direction = Head_Left;
			picture_animation->OnMove(L_Walking);
		}
	}
	void Archer::rightAnimation()
	{
		bool gothrough = true;
		if(attackMove)
			gothrough = false;
		if(!leftMove&&gothrough)
		{
			head_Direction = Head_Right;
			picture_animation->OnMove(R_Walking);
		}
	}
	void Archer::upAnimation()
	{
		bool gothrough = true;
		if(attackMove)
			gothrough = false;
		if(head_Direction == Head_Left&&gothrough)
			picture_animation->OnMove(L_Jumping);
		if(head_Direction == Head_Right&&gothrough)
			picture_animation->OnMove(R_Jumping);
	}
	void Archer::downAnimation()
	{
		bool gothrough = true;
		if(attackMove)
			gothrough = false;
		if(gothrough)
		{
			if(!isOnGround)
			{
				if(head_Direction == Head_Left)
					picture_animation->OnMove(L_Jumping);
				if(head_Direction == Head_Right)
					picture_animation->OnMove(R_Jumping);
			}
			else
			{
				bool check = false;
				if(isOnGround&&!attackMove)
					check = true;
				if(head_Direction == Head_Left&&check)
					picture_animation->OnMove(L_Walking);
				if(head_Direction == Head_Right&&check)
					picture_animation->OnMove(R_Walking);
			}
		}
	}
	void Archer::attackAnimation()
	{
			if(head_Direction == Head_Left)
				picture_animation->OnMove(L_Attacking);
			if(head_Direction == Head_Right)
				picture_animation->OnMove(R_Attacking);
	}




	void Archer::jumpUptimeParameter()
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
	void Archer::resetTimeParameter(bool JumpOrFall)
	{
		timeNow = timePast  = 0;
		timeUpLimit = interval_time * 10;
	}
	int Archer::gravity(double Vo,double g,double Time,double PriTime)
    {
		double delta_t = Time-PriTime;
        int GravityX = 0;
        GravityX = (int)((Vo * delta_t) - (g / 2) *((Time * Time)-(PriTime*PriTime)));
        return GravityX;
    }
	bool Archer::dojump()
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


	bool Archer::GetAttacking()
	{
		return attackMove;
	}
	bool Archer::GetRestartGame()
	{
		if(GetY() > SIZE_Y)
			return true;
		return false;
	}

	
	string Archer::WhatMyPoisition()
	{
		return "Archer";
	}