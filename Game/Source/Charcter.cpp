#include "StdAfx.h"
#include "Charcter.h"


	Charcter::Charcter():Human(SIZE_X/2-50,0)
	{
		upMove = downMove = rightMove = leftMove = false;
		upRestriction=downRestriction=rightRestriction=leftRestriction = false;
	}
	void Charcter::OnMove()
	{
		if (leftMove)
		{
			leftMoving();
			picture_animation.OnMove();
		}
		if (rightMove)
		{
			rightMoving();
			picture_animation.OnMove();
		}
		if (upMove)
			upMoving();
		if (downMove)
			downMoving();
		myRect.SetOriginRectangle(SIZE_X/2-50,GetY(),picture_animation.Width(),picture_animation.Height(),5);//SIZE_X/2-50
	}
	void Charcter::LoadBitmap()
	{
		char *RWalking[2] = {"Bitmaps/r_stand.bmp","Bitmaps/r_run.bmp"};
		picture_animation.LoadAnimation(R_Walking,RWalking,2);
		picture_animation.StateInitialize();
		picture_animation.SetTopLeft(GetX(),GetY());
	}
	void Charcter::OnShow()
	{
		picture_animation.SetTopLeft(SIZE_X/2-50,GetY());//SIZE_X/2-50
		picture_animation.OnShow(R_Walking);
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
		{
			GetX()+= speed;
		}
			/*else
				x += speed;*/
	}
	void Charcter::upMoving()
	{
		int speed = 5;
		if(getUpRestriction())
		{
			if(!(GetY() <= upBoundedValue))
				GetY()-= speed;
		}
		else
		{
			GetY()-= speed;
		}

	/*		else
				y -= speed;*/
	}
	void Charcter::downMoving()
	{
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
