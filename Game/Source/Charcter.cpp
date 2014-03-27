#include "StdAfx.h"
#include "Charcter.h"


	Charcter::Charcter():Human(SIZE_X/2-50,0)
	{
		upMove = downMove = rightMove = leftMove = false;
		upRestriction=downRestriction=rightRestriction=leftRestriction = false;
		resetJumping(true);
		//g = 10;
	}
	void Charcter::OnMove()
	{
		if (leftMove)
			leftMoving();
		if (rightMove)
			rightMoving();
		if (upMove)
			upMoving();
		if (!upMove)
			downMoving();
		if(!leftMove&&!rightMove&&!upMove&&!downMove)
			picture_animation.Reset();
		myRect.SetOriginRectangle(SIZE_X/2-50,GetY(),picture_animation.Width(),picture_animation.Height(),5);//SIZE_X/2-50
	}
	void Charcter::LoadBitmap()
	{
		char *RWalking[2] = {"Bitmaps/r_stand.bmp","Bitmaps/r_run.bmp"};
		char *LWalking[2] = {"Bitmaps/L_stand.bmp","Bitmaps/L_run.bmp"};
		picture_animation.LoadAnimation(R_Walking,RWalking,2);
		picture_animation.LoadAnimation(L_Walking,LWalking,2);
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
			picture_animation.OnMove(L_Walking);

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
			picture_animation.OnMove(R_Walking);
			/*else
				x += speed;*/
	}
	void Charcter::upMoving()
	{
		timeNow+= 0.1f;
		int speed = 5;
		int deltaY = gravity(falling_speed,g,timeNow,timePast);

		if(getUpRestriction())
		{
			if(!(GetY() <= upBoundedValue))
				GetY()-= deltaY;
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

	int Charcter::gravity(double Vo,double g,double Time,double PriTime)
    {
        int GravityX = 0;
        GravityX = (int)((Vo * (Time-PriTime)) - (g / 2) *((Time * Time)-(PriTime*PriTime)));
        return GravityX;
    }
	void Charcter::resetJumping(bool JumpOrFall)
	{
		falling_speed = 100;
		g = 30;
		timeNow = timePast  = 0;
	}

	void Charcter::downMoving()
	{
		resetJumping(true);
		int speed = 5;
		int height = picture_animation.Height();
		if(getDownRestriction())
		{
			if(!(GetY() + height >= downBoundedValue))
				GetY() += speed;
		}
		else
				GetY() += speed;
	}
