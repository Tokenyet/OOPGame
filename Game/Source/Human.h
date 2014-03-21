#ifndef HUMAN_H
#define HUMAN_H
#include "StdAfx.h"
//#include "gamelib.h"
#include "Equipment.h"
#include "Inventory.h"
#include "ICollision.h"
#include "CRectangle.h"
#include "Bounding_Obs.h"

class Human
{
private:
	int x,y;
	const int origin_X,origin_Y;
	//int slove_origin_X;//MyRect需要用到
	//CRectangle myRect;
	Bounding_Obs myRect;
	//Status status;
	//CAnimation humanAnimation;
	game_framework::CMovingBitmap picture;
	Equipment equipment;
	Inventory inventory;
	void walkng();
	void jump();
	void attack();
	bool upMove,downMove,rightMove,leftMove;
public:
	Human();
	//void SetScreenSize(int width,int height);
	void SetLocation(int x,int y);
	int &GetX();
	int &GetY();
	void LoadBitmap(char *,COLORREF RGB);//For test to side scrolling
	void KeyDownDetect(UINT keyin);
	void KeyUpDetect(UINT keyin);
	void OnMove();
	void OnShow();
	void AddThing(Thing Item);
	const int GetOriginX();
	const int GetOriginY();
	const int GetDistanceFromOriginX();
	Bounding_Obs GetRect();
};
#endif