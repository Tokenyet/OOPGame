#include "stdafx.h"
#include "Thing.h"
#include <WinDef.h>
#include "Human.h"

	Thing::Thing(const int init_x,const int init_y):origin_x(init_x),origin_y(init_y)
	{
		x= init_x;
		y= init_y;
		owner = NULL;
		myItemType = Type_NoItem;
	}
	Thing::~Thing()
	{
		if(owner==NULL)
		delete owner;
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
	const UsingItem Thing::GetThingType()
	{
		return myItemType;
	}
	bool Thing::HasOwner()
	{
		if(owner==NULL)
			return false;
		return true;
	}


		
	
	Arrow_Equip::Arrow_Equip(const int init_x,const int init_y):Thing(init_x,init_y)
	{
		myItemType = Type_Archer_Suit;
	}


	void Arrow_Equip::LoadBitmap(char *,COLORREF RGB)
	{
		Thing::LoadBitmap("Bitmaps/L/l_arror-1.bmp",RGB(0,0,0));
	}


	Mage_Equip::Mage_Equip(const int init_x,const int init_y):Thing(init_x,init_y)
	{
		myItemType = Type_Mage_Suit;
	}

	void Mage_Equip::LoadBitmap(char *,COLORREF RGB)
	{
		Thing::LoadBitmap("Bitmaps/L/l_magicball.bmp",RGB(0,0,0));
	}



