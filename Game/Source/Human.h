#ifndef HUMAN_H
#define HUMAN_H
#include "StdAfx.h"
//#include "gamelib.h"
#include "Equipment.h"
#include "Inventory.h"
#include "CRectangle.h"
#include "Bounding_Obs.h"
#include "Animation.h"
#include "Ewalk.h"

class Human
{
private:
	int x,y;
	const int origin_X,origin_Y;
	int width,height;
	//int slove_origin_X;//MyRect�ݭn�Ψ�
	//CRectangle myRect;
	//Status status;
	//CAnimation humanAnimation;
	Equipment equipment;
	Inventory inventory;
protected : 
	HeadDirection head_Direction;
	Animation picture_animation;
	game_framework::CMovingBitmap picture;//�~�Ӵ��ϥ�
	bool upRestriction,downRestriction,rightRestriction,leftRestriction; //�ǥ�Method���ѥ~���]�w
	int upBoundedValue,downBoundedValue,rightBoundedValue,leftBoundedValue; //Restriction true give direction�{�ɭ�
	bool upMove,downMove,rightMove,leftMove;//key ��L����  --�q���ۦ�]�w
	bool attackMove;
	Bounding_Obs myRect; //�I������
	virtual void leftMoving();//���ʼҦ��i�мg �D���n�мg�P�_�� ������q�Ƽg
	virtual void rightMoving();
	virtual void upMoving();
	virtual void downMoving();
	void setMySize(int width,int height);
public:
	Human(int initial_X,int initial_Y);
	~Human();
	//void SetScreenSize(int width,int height);
	void SetLocation(int x,int y);
	int &GetX();
	int &GetY();
	int GetWidth();
	int GetHeight();
	virtual void LoadBitmap(char * path,COLORREF RGB);//For test to side scrolling
	void KeyDownDetect(UINT keyin);
	void KeyUpDetect(UINT keyin);
	virtual void OnMove();
	virtual void OnShow();
	void AddThing(Thing Item);
	const int GetOriginX();
	const int GetOriginY();
	const int GetDistanceFromOriginX();
	Bounding_Obs GetRect();
	///Static///
	bool& setUpRestriction(int bounded_Up);
	bool& setDownRestriction(int bounded_Down);
	bool& setRightRestriction(int bounded_Right);
	bool& setLeftRestriction(int bounded_Left);
	bool getUpRestriction();
	bool getDownRestriction();
	bool getRightRestriction();
	bool getLeftRestriction();
	void ResetRestriction();
	///Dynamic///
	/*bool& setUpRestriction(int bounded_Up,int speed);
	bool& setDownRestriction(int bounded_Down,int speed);
	bool& setRightRestriction(int bounded_Right,int speed);
	bool& setLeftRestriction(int bounded_Left,int speed);*/
	
};
#endif