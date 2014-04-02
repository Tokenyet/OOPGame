#include "StdAfx.h"
#include "Enemy.h"

	Enemy::Enemy(int initial_X,int initial_Y):Human(initial_X,initial_Y)
	{
		interval_time = 0.5f;
		resetTimeParameter(true);
	}

	void Enemy::walking_nearby()
	{
		picture_animation.OnMove(R_Walking);
		GetX() -= 1;
		//GetX() += 5;
	}

	void Enemy::OnMove()
	{
		walking_nearby();/*
		if (leftMove)
			leftMoving();
		if (rightMove)
			rightMoving();
		/*if (dojump())
			upMoving();
		if (!isOnSky)*/
			downMoving();
	/*	if(!leftMove&&!rightMove&&!upMove&&!downMove)
			picture_animation.Reset();*/
		myRect.SetOriginRectangle(GetX(),GetY(),picture_animation.Width(),picture_animation.Height(),5);//SIZE_X/2-50
	}
	void Enemy::LoadBitmap()
	{
		char *RWalking[2] = {"Bitmaps/r_mushroom.bmp","Bitmaps/l_mushroom.bmp"};
		char *LWalking[2] = {"Bitmaps/l_mushroom.bmp","Bitmaps/r_mushroom.bmp"};

		picture_animation.LoadAnimation(R_Walking,RWalking,2);
		picture_animation.LoadAnimation(L_Walking,LWalking,2);
		picture_animation.StateInitialize();
		picture_animation.SetTopLeft(GetX(),GetY());
	}
	void Enemy::OnShow()
	{
		picture_animation.SetTopLeft(GetX(),GetY());//SIZE_X/2-50
		picture_animation.OnShow();
	}


	void Enemy::downMoving()
	{

		/*if(head_Direction == Head_Left)
				picture_animation.OnMove(L_Jumping);
		if(head_Direction == Head_Right)
				picture_animation.OnMove(R_Jumping);
		}
		else
		{*/
	/*		if(head_Direction == Head_Left&&isOnGround)
				picture_animation.OnMove(L_Walking);
			if(head_Direction == Head_Right&&isOnGround)*/
	//	}

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


	void Enemy::resetTimeParameter(bool JumpOrFall)
	{
		timeNow = timePast  = 0;
	}
	
	int Enemy::gravity(double Vo,double g,double Time,double PriTime)
    {
		double delta_t = Time-PriTime;
        int GravityX = 0;
        GravityX = (int)((Vo * delta_t) - (g / 2) *((Time * Time)-(PriTime*PriTime)));
        return GravityX;
    }