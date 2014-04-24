#include "stdafx.h"
#include "Thing.h"
#include <WinDef.h>
#include "Human.h"

	Thing::Thing(const int init_x,const int init_y):origin_x(init_x),origin_y(init_y)
	{
		x= init_x;
		y= init_y;
		owner = NULL;
	}
	int& Thing::GetX(){ return x;}
	int& Thing::GetY(){ return y;}
	void Thing::OnMove()
	{
		if(!picture.isBitmapLoaded)
			LoadBitmap("Bitmaps/ball1.bmp",RGB(0,0,0));
		picture.SetTopLeft(x,y);
		myRect.SetRectangle(x,y,picture.Width(),picture.Height());
	}
	void Thing::OnShow()
	{
		if(!picture.isBitmapLoaded)
		{
			LoadBitmap("Bitmaps/ball1.bmp",RGB(0,0,0));
			picture.SetTopLeft(origin_x,origin_y);
		}
		if(owner == NULL)
		{
			picture.ShowBitmap();
		}
	}
	void Thing::LoadBitmap(char * path,COLORREF RGB)
	{
		picture.LoadBitmapA(path,RGB);
		myRect.SetRectangle(x,y,picture.Width(),picture.Height());
	}
	const int Thing::GetOriginX(){return origin_x;}
	const int Thing::GetOriginY(){return origin_y;}
	void Thing::MakeOwnerBy(Human* newOwner)
	{
		if(newOwner == NULL)
			owner = NULL;
		else
			owner = newOwner;
	}
	CRectangle Thing::GetRect()
	{
		return myRect;
	}
	const string Thing::GetName(){return "New";}
	bool Thing::HasOwner()
	{
		if(owner==NULL)
			return false;
		return true;
	}