#ifndef THING_H
#define THING_H
#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
#include "IPerform.h"


class Thing : IPerform
{
private:
	int x,y;
	game_framework::CMovingBitmap picture;
public:
	int &GetX();
	int &GetY();
	void OnMove();
	void OnShow();
	void LoadBitmap(char *,COLORREF RGB);
};
#endif