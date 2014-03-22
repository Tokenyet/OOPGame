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
	bool upMove,downMove,rightMove,leftMove;//key
	bool upRestriction,downRestriction,rightRestriction,leftRestriction;
	int upBoundedValue,downBoundedValue,rightBoundedValue,leftBoundedValue;
	void walkng();
	void jump();
	void attack();
	bool getUpRestriction();
	bool getDownRestriction();
	bool getRightRestriction();
	bool getLeftRestriction();
	void leftMoving();
	void rightMoving();
	void upMoving();
	void downMoving();
	void resetRestriction();
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
	bool& setUpRestriction(int bounded_Up);
	bool& setDownRestriction(int bounded_Down);
	bool& setRightRestriction(int bounded_Right);
	bool& setLeftRestriction(int bounded_Left);
	
};
#endif