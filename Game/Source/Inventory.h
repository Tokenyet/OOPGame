#ifndef INVENTORY_H
#define INVENTORY_H
#include "StdAfx.h"
#include "gamelib.h"
#include <vector>
#include "Thing.h"
//#include "Human.h"

class Inventory
{
private:
	int x,y;
	vector<Thing> things;
	//Human* owner;
	game_framework::CMovingBitmap picture;
	void changeClothes();
	void addHealth();
public:
	void AddThings(Thing);
	void Peek(Thing);
	void OnShow();
};
#endif