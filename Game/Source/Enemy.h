#ifndef ENEMY_H
#define ENEMY_H

#include "Human.h"
#include "Gravity.h"
#include "IRoleType.h"

class Enemy : public Human
{
//private :
protected:
	IRoleType *myType;
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
	virtual void MovingAI();
public:
	Enemy(int initial_X,int initial_Y,CharcterType);
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


class Enemy_OverWall :public Enemy
{
public:
	Enemy_OverWall(int initial_X,int initial_Y,CharcterType);
	~Enemy_OverWall();
	void MovingAI();
};
#endif
