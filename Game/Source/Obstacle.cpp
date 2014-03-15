#include "StdAfx.h"
#include "Obstacle.h"

	Obstacle::Obstacle()
	{x=y=100;}
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
	}
	int& Obstacle::GetX(){return x;}
	int& Obstacle::GetY(){return y;}