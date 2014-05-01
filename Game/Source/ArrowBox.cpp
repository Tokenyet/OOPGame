#include "StdAfx.h"
#include "ArrowBox.h"



	ArrowBox::ArrowBox(const int init_x,const int init_y,const HeadDirection head):origin_x(init_x),origin_y(init_y),head(this->head)
	{
		x= init_x;
		y= init_y;
		LoadBitmap(head);
	}
	void ArrowBox::LoadBitmap(HeadDirection head)
	{
		if(head == Head_Left)
			picture.LoadBitmapA("Bitmaps/L/l_arror-1");
		else if (head == Head_Right)
			picture.LoadBitmapA("Bitmaps/R/r_arror-1");
		myRect.SetRectangle(x,y,picture.Width(),picture.Height());
	}
	void ArrowBox::LoadBitmap(char * path)
	{
		picture.LoadBitmapA(path);
		myRect.SetRectangle(x,y,picture.Width(),picture.Height());
	}
	void ArrowBox::OnShow()
	{
		picture.ShowBitmap();
	}
	void ArrowBox::OnMove()
	{
		if(!picture.isBitmapLoaded)
			ASSERT(0);
		picture.SetTopLeft(x,y);
		myRect.SetRectangle(x,y,picture.Width(),picture.Height());
	}
	int& ArrowBox::GetX(){return x;}
	int& ArrowBox::GetY(){return y;}

	const int ArrowBox::GetOriginX(){return origin_x;}
	const int ArrowBox::GetOriginY(){return origin_y;}

	CRectangle ArrowBox::GetRect()
	{
		return myRect;
	}