#ifndef CHARCTER_H
#define CHARCTER_H
#include "StdAfx.h"
#include "Human.h"

class Charcter : public Human
{
protected:
	void leftMoving();
	void rightMoving();
	void upMoving();
	void downMoving();
public:
	Charcter();
	void OnMove();
	void OnShow();
	void LoadBitmap();
};
#endif