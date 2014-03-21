#include "StdAfx.h"
#include "Equipment.h"
#include "Inventory.h"
#include "IPerform.h"
#include "Human.h"
#include "Bounding_Obs.h"

	Human::Human():origin_X(SIZE_X/2-50),origin_Y(0)
	{
		upMove = downMove = rightMove = leftMove = false;
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
			x -=5;
		if (rightMove)
			x +=5;
		if (upMove)
			y -= 5;
		if (downMove)
			y += 5;
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