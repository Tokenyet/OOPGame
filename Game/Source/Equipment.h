#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "StdAfx.h"
#include "Thing.h"
//#include "Human.h"

class Thing;
class Equipment
{
private:
	//Human *human;
	Thing *equip;
	//It should be Suit but i haven't complete Thing
public:
	Thing* ChangeClothes();
	//if I have a clothes turn off to Inventory
};
#endif