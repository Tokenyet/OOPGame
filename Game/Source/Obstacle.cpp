#include "StdAfx.h"
#include "Obstacle.h"
#include "CRectangle.h"
	Obstacle::Obstacle()
	{x=y=300;collisionTF=false;}
	void Obstacle::LoadBitmap(char * path)
	{
		picture.LoadBitmapA(path);
	}
	void Obstacle::OnShow()
	{
		picture.ShowBitmap();
	}
	void Obstacle::OnMove()
	{
		picture.SetTopLeft(x,y);
		syncMyRect();
	}
	int& Obstacle::GetX(){return x;}
	int& Obstacle::GetY(){return y;}

	CRectangle Obstacle::GetRect(){return myRect; }
	bool& Obstacle::GetIntersect(int mode = 0){return collisionTF;}

	void Obstacle::syncMyRect()
	{
		myRect.SetRectangle(x,y,x+picture.Width(),y+picture.Height());
	}