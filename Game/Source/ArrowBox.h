#ifndef ARROWBOX_H
#define ARROWBOX_H
#pragma once
#include "IPerform.h"
#include <ddraw.h>
#include "gamelib.h"
#include "CRectangle.h"
#include "Human.h"//EWalk HeadDirection

class ArrowBox : public IPerform
{
private:
	int x,y;
	const int origin_x,origin_y;
	const HeadDirection head;
	game_framework::CMovingBitmap picture;
	CRectangle myRect;
public:
	ArrowBox(const int init_x,const int init_y,const HeadDirection head);
	void LoadBitmap(HeadDirection);
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
