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
			leftMoving();
		if (rightMove)
			rightMoving();
		if (upMove)
			upMoving();
		if (downMove)
			downMoving();
		picture.SetTopLeft(SIZE_X/2-50,GetY());//SIZE_X/2-50
		myRect.SetOriginRectangle(SIZE_X/2-50,GetY(),picture.Width(),picture.Height(),5);//SIZE_X/2-50
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
		int width = picture.Width();
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
		int height = picture.Height();
		if(getDownRestriction())
		{
			if(!(GetY() + height >= downBoundedValue))
				GetY() += speed;
		}
		else
				GetY() += speed;
	}
