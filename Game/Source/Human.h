#ifndef HUMAN_H
#define HUMAN_H
#include "StdAfx.h"
//#include "gamelib.h"
#include "Thing.h"
#include "Equipment.h"
#include "Inventory.h"
#include "CRectangle.h"
#include "Bounding_Obs.h"
#include "Animation.h"
#include "Ewalk.h"
#include "SkillSheet.h"
#include <sstream>

class Thing;
class Human
{
private:
	int x,y;
	const int origin_X,origin_Y;
	int width,height;
	Thing* myThing;
protected : 
	int health;
	HeadDirection head_Direction;
	SkillSheet mySkill;
	Animation *picture_animation;
	game_framework::CMovingBitmap picture;//繼承換圖用
	bool upRestriction,downRestriction,rightRestriction,leftRestriction; //藉由Method提供外部設定
	int upBoundedValue,downBoundedValue,rightBoundedValue,leftBoundedValue; //Restriction true give direction臨界值
	bool upMove,downMove,rightMove,leftMove;//key 鍵盤偵測  --電腦自行設定
	bool attackMove;
	Bounding_Obs myRect; //碰撞偵測
	virtual void leftMoving();//移動模式可覆寫 主角要覆寫判斷式 必須整段複寫
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
	virtual void LoadBitmap();
	virtual void LoadBitmap(char * path,COLORREF RGB);//For test to side scrolling
	void KeyDownDetect(UINT keyin);
	void KeyUpDetect(UINT keyin);
	virtual void OnMove();
	virtual void OnShow();
	virtual void AddThing(Thing* Item);
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
	void Reset();
	virtual bool GetAttacking();
	virtual bool GetRestartGame();
	virtual int MyType();
	virtual SkillSheet MySkillSheet();
	HeadDirection GetHeadDirection();
	bool GetHurt(int hurtValue);
	///Dynamic///
	/*bool& setUpRestriction(int bounded_Up,int speed);
	bool& setDownRestriction(int bounded_Down,int speed);
	bool& setRightRestriction(int bounded_Right,int speed);
	bool& setLeftRestriction(int bounded_Left,int speed);*/
	
};
static 	void MessageShow(int x ,int y,int health)
	{
		CDC *pDC = game_framework::CDDraw::GetBackCDC();
		CFont f,*fp;
		f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
		fp=pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(255,255,0));
		stringstream ss;
		ss << health;
		string str = ss.str();
		pDC->TextOut(x,y,str.c_str());
		game_framework::CDDraw::ReleaseBackCDC();
	}
#endif