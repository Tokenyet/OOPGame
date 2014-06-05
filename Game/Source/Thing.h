#ifndef THING_H
#define THING_H
#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
#include "Human.h"
#include "IPerform.h"
#include "CRectangle.h"
#include <string>

enum UsingItem
{
	Type_NoItem = 0,
	Type_SwordMan_Suit = 1,
	Type_Archer_Suit = 2,
	Type_Mage_Suit = 3,
};


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
protected:
	UsingItem myItemType;
public:
	Thing(const int init_x,const int init_y);
	~Thing();
	int &GetX();
	int &GetY();
	void OnMove();
	void OnShow();
	virtual void LoadBitmap(char *,COLORREF RGB);
	void MakeOwnerBy(Human*);
	const int GetOriginX();
	const int GetOriginY();
	CRectangle GetRect();
	const UsingItem GetThingType();
	bool HasOwner();
};

class Arrow_Equip : public Thing
{
public:
	Arrow_Equip(const int init_x,const int init_y);
	void LoadBitmap(char *,COLORREF RGB);
};

class Mage_Equip :public Thing
{
public:
	Mage_Equip(const int init_x,const int init_y);
	void LoadBitmap(char *,COLORREF RGB);
};

#endif