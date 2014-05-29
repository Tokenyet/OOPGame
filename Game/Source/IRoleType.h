#ifndef IROLETYPE_H
#define IROLETYPE_H
#include "Human.h"
#include "Animation.h"
#include "SkillSheet.h"
#include "Gravity.h"
#include "SkillSheet.h"
class Human;

enum CharcterType
{
	Type_Null = 0,
	Type_SwordMan = 1,
	Type_Archer = 2,
	Type_Mage = 3,
};

class IRoleType
{
private :
	/*
	double interval_time;
	double timeUpLimit;
	double timeNow,timePast;
	void resetTimeParameter(bool JumpOrFall);
	int gravity(double Vo,double g,double Time,double PriTime);
	void jumpUptimeParameter();
	bool isOnGround,isOnSky,isKeepUpMove;
	bool dojump();*/
	//HeadDirection *head_Direction;
protected:
	Human *human;
	Animation picture_animation;
	SkillSheet mySkill;
	/*bool upRestriction,downRestriction,rightRestriction,leftRestriction; //�ǥ�Method���ѥ~���]�w
	int upBoundedValue,downBoundedValue,rightBoundedValue,leftBoundedValue; //Restriction true give direction�{�ɭ�
	bool upMove,downMove,rightMove,leftMove;//key ��L����  --�q���ۦ�]�w
	bool attackMove;
	Bounding_Obs myRect; //�I������*/
	//void setMySize(int width,int height);
public:
	IRoleType(Human *human);
	virtual ~IRoleType();
	virtual void LeftMoving();
	virtual void LeftMoving(bool);
	virtual void LeftAnimation();
	virtual void RightMoving();
	virtual void RightMoving(bool);
	virtual void RightAnimation();
	virtual void UpMoving();
	virtual void UpMoving(bool);
	virtual void UpAnimation();
	virtual void DownMoving();
	virtual void DownMoving(bool);
	virtual void DownAnimation();
	virtual void AttackMoving();
	virtual void AttackAnimation();
	virtual bool GetUpController(bool);
	virtual bool GetDownController(bool);
	virtual bool GetLeftController(bool);
	virtual bool GetRightController(bool);
	virtual void OnShow(int x,int y);
	virtual void LoadBitmap();
	virtual void AnimationReset();
	virtual bool GetContinueAttack();
	void ResetAnimation();
	int GetWidth();
	int GetHeight();
	virtual CharcterType MyType();
	virtual SkillSheet MySkillSheet();
};

class SwordMan :public IRoleType
{
private:
	Gravity *myGravity;
public:
	SwordMan(Human *human);
	~SwordMan();
	virtual void LeftMoving();
	virtual void LeftAnimation();
	virtual void RightMoving();
	virtual void RightAnimation();
	virtual void UpMoving(bool);
	virtual void UpAnimation();
	virtual void DownMoving(bool);
	virtual void DownAnimation();
	virtual void AttackMoving();
	virtual void AttackAnimation();
	virtual void OnShow(int x,int y);
	virtual void LoadBitmap();
	virtual CharcterType MyType();
	virtual bool GetContinueAttack();
	virtual bool GetUpController(bool);
	virtual bool GetDownController(bool);
	virtual bool GetLeftController(bool);
	virtual bool GetRightController(bool);
};



class Archer :public SwordMan
{
private:
	Gravity *myGravity;
public:
	Archer(Human *human);
	~Archer();
	void AttackMoving();
	virtual void LoadBitmap();
	virtual CharcterType MyType();
};


class Mage :public SwordMan
{
private:
	Gravity *myGravity;
public:
	Mage(Human *human);
	~Mage();
	void AttackMoving();
	virtual void LoadBitmap();
	virtual CharcterType MyType();
	virtual bool GetContinueAttack();
};


#endif