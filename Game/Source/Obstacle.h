#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "ICollision.h"
#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
#include "CRectangle.h"

class Obstacle : public ICollision
{
private:
	int x,y;
	const int origin_x,origin_y;
	game_framework::CMovingBitmap picture;
	CRectangle myRect;
	bool deadly;
public:
	Obstacle(const int init_x,const int init_y);
	void LoadBitmap(char *);
	void OnShow();
	void OnMove();
	int& GetX();
	int& GetY();
	const int GetOriginX();
	const int GetOriginY();
	CRectangle GetRect();
};
#endif