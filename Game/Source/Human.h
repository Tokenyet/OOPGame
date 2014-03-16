#ifndef HUMAN_H
#define HUMAN_H
#include "StdAfx.h"
#include "gamelib.h"
#include "Equipment.h"
#include "Inventory.h"
#include "IPerform.h"
#include "ICollision.h"
#include "CRectangle.h"

class Human : public IPerform,public ICollision
{
private:
	int x,y;
	//Status status;
	//CAnimation humanAnimation;
	game_framework::CMovingBitmap picture;
	Equipment equipment;
	Inventory inventory;
	void walkng();
	void jump();
	void attack();
	bool upMove,downMove,rightMove,leftMove;
	CRectangle myRect;
	bool collisionRT[6];//wall上wall下wall左wall右額外額外
	void syncMyRect();
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
	CRectangle GetRect();
	bool &GetIntersect(int);
};
#endif