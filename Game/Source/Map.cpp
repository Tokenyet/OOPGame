#include "stdafx.h"
#include "Map.h"

	Map::Map()
	{
		movX=movY = 0;
	}
	Map::~Map()
	{
	}
	void Map::Initialize(int width,int heigth,char* path)
	{	
		SetScreenSize(width,heigth);
		LoadMap(path);
	}
	void Map::SetScreenSize(int width,int height)
	{
		windows_Width = width;
		windows_Heigth = height;
	}
	int& Map::GetX(){return movX;}
	int& Map::GetY(){return movY;}
	void Map::SetMapLocation(int x,int y)
	{
		movX = x;
		movY = y;
		picture.SetTopLeft(x,y);
	}
	bool Map::CheckWidthOutOfWindowsLeft()
	{
		int picture_Width = picture.Width();
		if((movX+picture_Width) <= 0)//圖向左移動 人向右移動
			return true;
		return false;
	}
	bool Map::CheckWidthOutOfWindowsRight()
	{
		int picture_Width = picture.Width();
		if(movX >= windows_Width)
			return true;
		return false;
	}
	bool Map::CheckWidthOnLeftBorder()
	{
		int picture_Width = picture.Width();
		if(movX >= 0)
			return true;
		return false;
	}
	void Map::OnShow()
	{
		picture.ShowBitmap();
	}
	void Map::OnMove()
	{
		picture.SetTopLeft(movX,movY);
	}
	void Map::LoadMap(char * path)
	{
		picture.LoadBitmapA(path);
	}
	int Map::GetWidth()
	{
		return picture.Width();
	}
	int Map::GetHeight()
	{
		return picture.Height();
	}