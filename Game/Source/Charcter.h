#ifndef CHARCTER_H
#define CHARCTER_H
#include "StdAfx.h"
#include "Human.h"
#include "Gravity.h"
#include "IRoleType.h"

class Charcter : public Human
{
private :
	IRoleType *myType;
	bool nextStage; //trash..
protected:
	void leftMoving();
	void leftAnimation();
	void rightMoving();
	void rightAnimation();
	void upMoving();
	void upAnimation();
	void downMoving();
	void downAnimation();
	void attackMoving();
	void attackAnimation();
public:
	Charcter();
	~Charcter();
	void OnMove();
	void OnShow();
	void AddThing(Thing*);
	void LoadBitmap();
	bool GetAttacking();
	bool GetRestartGame();
	bool GetNextStage();//trash
	int MyType();
	SkillSheet MySkillSheet();
};
#endif