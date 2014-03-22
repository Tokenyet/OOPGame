#include "StdAfx.h"
#include "Equipment.h"
#include "Inventory.h"
#include "IPerform.h"
#include "Human.h"
#include "Bounding_Obs.h"

	Human::Human():origin_X(SIZE_X/2-50),origin_Y(0)
	{
		upMove = downMove = rightMove = leftMove = false;
		upRestriction=downRestriction=rightRestriction=leftRestriction = false;
		x = y = 0;
		x = origin_X;
		//y = SIZE_Y/2; //Must Know My Width Of Picture
	}
	void Human::SetLocation(int x,int y)
	{
/*		this->x = (SIZE_X - picture.Width())/2;
		this->y = SIZE_Y/2 + 50;//- picture.Height();*/
	}
	int& Human::GetX(){return x;}
	int& Human::GetY(){return y;}
	void Human::KeyDownDetect(UINT keyin)
	{
		const char KEY_LEFT  = 0x25; // keyboard左箭頭
		const char KEY_UP    = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN  = 0x28; // keyboard下箭頭
		if(keyin == KEY_LEFT)
			leftMove = true;
		if(keyin == KEY_UP)
			upMove = true;
		if(keyin == KEY_DOWN)
			downMove = true;
		if(keyin == KEY_RIGHT)
			rightMove = true;
	}
	void Human::KeyUpDetect(UINT keyin)
	{
		const char KEY_LEFT  = 0x25; // keyboard左箭頭
		const char KEY_UP    = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN  = 0x28; // keyboard下箭頭
		if(keyin == KEY_LEFT)
			leftMove = false;
		if(keyin == KEY_UP)
			upMove = false;
		if(keyin == KEY_DOWN)
			downMove = false;
		if(keyin == KEY_RIGHT)
			rightMove = false;
	}
	void Human::OnMove()
	{
		if (leftMove)
			leftMoving();
		if (rightMove)
			rightMoving();
		if (upMove)
			upMoving();
		if (downMove)
			downMoving();
		resetRestriction();
		picture.SetTopLeft(x,y);
		myRect.SetOriginRectangle(x,y,picture.Width(),picture.Height(),5);
	}
	void Human::OnShow()
	{
		picture.ShowBitmap();
	}
	void Human::AddThing(Thing Item){}
	void Human::LoadBitmap(char * path,COLORREF RGB)//For test to side scrolling
	{
		picture.LoadBitmapA(path,RGB);
		myRect.SetOriginRectangle(x,y,picture.Width(),picture.Height(),5);
	}
	const int Human::GetOriginX(){return 0;}
	const int Human::GetOriginY(){return 0;}
	const int Human::GetDistanceFromOriginX()
	{
		return GetX() - origin_X;
	}

	Bounding_Obs Human::GetRect()
	{
		return myRect;
	}

	bool& Human::setUpRestriction(int bounded_Up)
	{
		upBoundedValue = bounded_Up;
		return upRestriction;
	}
	bool& Human::setDownRestriction(int bounded_Down)
	{
		downBoundedValue = bounded_Down;
		return downRestriction;
	}
	bool& Human::setRightRestriction(int bounded_Right)
	{
		rightBoundedValue = bounded_Right;
		return rightRestriction;
	}
	bool& Human::setLeftRestriction(int bounded_Left)
	{
		leftBoundedValue = bounded_Left;
		return leftRestriction;
	}

	bool Human::getUpRestriction()
	{
		return upRestriction;
	}
	bool Human::getDownRestriction()
	{
		return downRestriction;
	}
	bool Human::getRightRestriction()
	{
		return rightRestriction;
	}
	bool Human::getLeftRestriction()
	{
		return leftRestriction;
	}

	void Human::leftMoving()
	{
		int speed = 5;
		x -= speed;
		if(getLeftRestriction())
			if(x <= leftBoundedValue)
				x = leftBoundedValue;
			/*else
				x -= speed;*/
	}
	void Human::rightMoving()
	{
		int speed = 5;
		int width = picture.Width();
		x += speed;
		if(getRightRestriction())
			if(x + width>= rightBoundedValue)
				x = rightBoundedValue - width;
			/*else
				x += speed;*/
	}
	void Human::upMoving()
	{
		int speed = 5;
		y -= speed;
		if(getUpRestriction())
			if(y <= upBoundedValue)
				y = upBoundedValue;
	/*		else
				y -= speed;*/
	}
	void Human::downMoving()
	{
		int speed = 5;
		int height = picture.Height();
		y += speed;
		if(getDownRestriction())
			if(y + height >= downBoundedValue)
				y = downBoundedValue - height;
/*			else
				y += speed;*/
	}

	void Human::resetRestriction()
	{
		upRestriction=downRestriction=rightRestriction=leftRestriction = false;
		upBoundedValue=downBoundedValue=rightBoundedValue=leftBoundedValue = 0;
	}