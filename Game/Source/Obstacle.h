#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "IPerform.h"
#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"

class Obstacle : public IPerform
{
private:
	int x,y;
	game_framework::CMovingBitmap picture;
	bool deadly;
public:
	Obstacle();
	void LoadBitmap(char *);
	void OnShow();
	void OnMove();
	int& Obstacle::GetX();
	int& Obstacle::GetY();
};
#endif