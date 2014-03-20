#include "StdAfx.h"
#include "Obstacle.h"




Obstacle::Obstacle(const int init_x,const int init_y):origin_x(init_x),origin_y(init_y)
	{
		x= init_x;
		y= init_y;
	}
	void Obstacle::LoadBitmap(char * path)
	{
		picture.LoadBitmapA(path);
		myRect.SetRectangle(x,y,picture.Width(),picture.Height());
	}
	void Obstacle::OnShow()
	{
		picture.ShowBitmap();
	}
	void Obstacle::OnMove()
	{
		picture.SetTopLeft(x,y);
		myRect.SetRectangle(x,y,picture.Width(),picture.Height());
	}
	int& Obstacle::GetX(){return x;}
	int& Obstacle::GetY(){return y;}

	const int Obstacle::GetOriginX(){return origin_x;}
	const int Obstacle::GetOriginY(){return origin_y;}

	CRectangle Obstacle::GetRect()
	{
		return myRect;
	}