#ifndef THING_H
#define THING_H
#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
#include "Human.h"
#include "IPerform.h"
#include "CRectangle.h"
#include <string>

class Human;
class Thing : public IPerform
{
private:
	int x,y;
	const int origin_x,origin_y;
	string itemName;
	game_framework::CMovingBitmap picture;
	CRectangle myRect;
	Human *owner;
public:
	Thing(const int init_x,const int init_y);
	~Thing();
	int &GetX();
	int &GetY();
	void OnMove();
	void OnShow();
	void LoadBitmap(char *,COLORREF RGB);
	void MakeOwnerBy(Human*);
	const int GetOriginX();
	const int GetOriginY();
	CRectangle GetRect();
	const string GetName();
	bool HasOwner();
	
};
#endif