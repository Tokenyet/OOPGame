#include "StdAfx.h"
#include "Enemy.h"
#include "Ewalk.h"

	Enemy::Enemy(int initial_X,int initial_Y):Human(initial_X,initial_Y)
	{
		interval_time = 0.5f;
		timeNow = timePast = 0;
		walk_Behavior = new Nomal_Walking();
		myGravity_Behavior = new Normal_Gravity();
		head_Direction = Head_Left;
	}

	Enemy::~Enemy()
	{
		delete walk_Behavior;
		delete myGravity_Behavior;
	}

	void Enemy::walking_nearby()
	{
		int width = picture_animation.Width();
		picture_animation.OnMove(R_Walking);
		walk_Behavior->Walk(GetX(),GetY(),rightRestriction,leftRestriction
			,rightBoundedValue,leftBoundedValue,1,width,head_Direction);
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
		myGravity_Behavior->JumpOrFall(GetY(),upRestriction,downRestriction,upBoundedValue,
			downBoundedValue,timeRestriction,timeNow,timePast,
			interval_time,picture_animation.Height(),false);
	}
