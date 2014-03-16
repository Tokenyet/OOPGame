#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "IPerform.h"
#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
#include "ICollision.h"
#include "CRectangle.h"

class Obstacle : public IPerform,public ICollision
{
private:
	int x,y;
	game_framework::CMovingBitmap picture;
	bool deadly;
	CRectangle myRect;
	bool collisionTF;
	void syncMyRect();
public:
	Obstacle();
	void LoadBitmap(char *);
	void OnShow();
	void OnMove();
	int& Obstacle::GetX();
	int& Obstacle::GetY();

	CRectangle GetRect();
	bool &GetIntersect(int);
};
#endif