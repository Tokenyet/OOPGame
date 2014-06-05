#ifndef ENEMY_H
#define ENEMY_H

#include "Human.h"
#include "Gravity.h"
#include "IRoleType.h"

class Enemy : public Human
{
private :
	IRoleType *myType;
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
	IRoleType* GetMyType(CharcterType);
public:
	Enemy(int initial_X,int initial_Y);
	~Enemy();
	void OnMove();
	void OnShow();
	void AddThing(Thing*);
	void LoadBitmap();
	bool GetAttacking();
	bool GetRestartGame();
	int MyType();
	SkillSheet MySkillSheet();
};




#endif
