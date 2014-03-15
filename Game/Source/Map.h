#ifndef MAP_H
#define MAP_H
#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
#include "ILocation.h"

class Map : public ILocation
{
private:
	int movX,movY;
	int windows_Width,windows_Heigth;
	game_framework::CMovingBitmap picture;
public:
	Map();
	~Map();
	void Initialize(int width,int heigth,char* path);
	void SetScreenSize(int width,int height);
	int &GetX();
	int &GetY();
	void SetMapLocation(int x,int y);
	bool CheckWidthOutOfWindowsLeft();
	bool CheckWidthOnLeftBorder();
	bool CheckWidthOutOfWindowsRight(); //人物往左走換地圖之判斷法
	void OnShow();
	void OnMove();
	void LoadMap(char *);//LoadBitmap
	int GetWidth();
	int GetHeight();
};
#endif