#include "StdAfx.h"
#include "IRoleType.h"
#include "Human.h"
#include "Charcter.h"
#include "Animation.h"
#include "Gravity.h"
#include "SkillSheet.h"


void IRoleType::LeftMoving()
{
	int &x = human->GetX();
	int speed = 5;
	x -= speed;
}
void IRoleType::LeftAnimation()
{
	picture_animation.OnMove(L_Walking);
}
void IRoleType::RightMoving()
{
	int &x = human->GetX();
	int speed = 5;
	x += speed;
}
void IRoleType::RightAnimation()
{
	picture_animation.OnMove(R_Walking);
}
void IRoleType::UpMoving()
{
	int &y = human->GetY();
	y -= 10;
}
void IRoleType::UpAnimation()
{
	HeadDirection head_Direction = human->GetHeadDirection();
	if(head_Direction == Head_Left)
		picture_animation.OnMove(L_Jumping);
	if(head_Direction == Head_Right)
		picture_animation.OnMove(R_Jumping);
}
void IRoleType::DownMoving()
{
		int &y = human->GetY();
		y+= 10;
}
void IRoleType::DownAnimation()
{
	HeadDirection head_Direction = human->GetHeadDirection();
	if(head_Direction == Head_Left)
		picture_animation.OnMove(L_Jumping);
	if(head_Direction == Head_Right)
		picture_animation.OnMove(R_Jumping);
}


void IRoleType::LeftMoving(bool function_enable)
{
	int &x = human->GetX();
	int speed = 5;
	x -= speed;
}
void IRoleType::RightMoving(bool function_enable)
{
	int &x = human->GetX();
	int speed = 5;
	x += speed;
}
void IRoleType::UpMoving(bool function_enable)
{
	int &y = human->GetY();
	y -= 10;
}
void IRoleType::DownMoving(bool function_enable)
{
		int &y = human->GetY();
		y+= 10;
}


void IRoleType::AttackMoving()
{}
void IRoleType::AttackAnimation()
{
	HeadDirection head_Direction = human->GetHeadDirection();
	if(head_Direction == Head_Left)
		picture_animation.OnMove(L_Attacking);
	if(head_Direction == Head_Right)
		picture_animation.OnMove(R_Attacking);
}



//void IRoleType::setMySize(int width,int height){}

IRoleType::IRoleType(Human *human)
{
	this->human = human;
	mySkill.AddSkill(Type_NoSkill,0);
}
IRoleType::~IRoleType(){}
void IRoleType::OnShow(int x,int y)
{
	picture_animation.SetTopLeft(x,y);//SIZE_X/2-50
	picture_animation.OnShow();
}
void IRoleType::LoadBitmap()
{
		int &x = human->GetX();
		int &y = human->GetY();
		char *RWalking[5] = {"Bitmaps/R/r_walk-1.bmp","Bitmaps/R/r_walk-2.bmp","Bitmaps/R/r_walk-3.bmp","Bitmaps/R/r_walk-2.bmp","Bitmaps/R/r_walk-1.bmp"};
		char *LWalking[5] = {"Bitmaps/L/l_walk-1.bmp","Bitmaps/L/l_walk-2.bmp","Bitmaps/L/l_walk-3.bmp","Bitmaps/L/l_walk-2.bmp","Bitmaps/L/l_walk-1.bmp"};
		char *RJumping[2] = {"Bitmaps/R/r_jump-1.bmp","Bitmaps/R/r_jump-2.bmp"};
		char *LJumping[2] = {"Bitmaps/L/l_jump-1.bmp","Bitmaps/L/l_jump-2.bmp"};
		char *RAttack[4] =  {"Bitmaps/R/r_attack-1.bmp","Bitmaps/R/r_attack-2.bmp","Bitmaps/R/r_attack-3.bmp","Bitmaps/R/r_attack-4.bmp"};
		char *LAttack[4] =  {"Bitmaps/L/l_attack-1.bmp","Bitmaps/L/l_attack-2.bmp","Bitmaps/L/l_attack-3.bmp","Bitmaps/L/l_attack-4.bmp"};
		
		picture_animation.LoadAnimation(R_Walking,RWalking,5,1);
		picture_animation.LoadAnimation(L_Walking,LWalking,5,1);
		picture_animation.LoadAnimation(R_Jumping,RJumping,2,1);
		picture_animation.LoadAnimation(L_Jumping,LJumping,2,1);
		picture_animation.LoadAnimation(R_Attacking,RAttack,4,0);
		picture_animation.LoadAnimation(L_Attacking,LAttack,4,0);
		picture_animation.StateInitialize();
		//setMySize(picture_animation->Width(),picture_animation->Height());
		picture_animation.SetTopLeft(x,y);
}
CharcterType IRoleType::MyType(){return Type_Null;}
void IRoleType::ResetAnimation()
{
	picture_animation.Reset();
}

int IRoleType::GetWidth(){return picture_animation.Width();}
int IRoleType::GetHeight(){return picture_animation.Height();}

bool IRoleType::GetUpController(bool upMove)
{
	return upMove;
}
bool IRoleType::GetDownController(bool downMove)
{
	return downMove;
}
bool IRoleType::GetLeftController(bool leftMove)
{
	return leftMove;
}
bool IRoleType::GetRightController(bool rightMove)
{
	return rightMove;
}
void IRoleType::AnimationReset()
{
	picture_animation.Reset();
}

bool IRoleType::GetContinueAttack()
{
	return false;
}
SkillSheet IRoleType::MySkillSheet()
{
	return mySkill;
}





void SwordMan::LeftMoving()
{
	int &x = human->GetX();
	int speed = 5;
	x -= speed;
}
void SwordMan::LeftAnimation()
{
	picture_animation.OnMove(L_Walking);
}
void SwordMan::RightMoving()
{
	int &x = human->GetX();
	int speed = 5;
	x += speed;
}
void SwordMan::RightAnimation()
{
	picture_animation.OnMove(R_Walking);
}
void SwordMan::UpMoving(bool function_enable)
{
	if(function_enable)
		myGravity->Jumping();
	else
	{
		myGravity->SetOnSky(false);
		myGravity->SetKeepUpMove(false);
	}
}
void SwordMan::UpAnimation()
{
	HeadDirection head_Direction = human->GetHeadDirection();
	if(head_Direction == Head_Left)
		picture_animation.OnMove(L_Jumping);
	if(head_Direction == Head_Right)
		picture_animation.OnMove(R_Jumping);
}
void SwordMan::DownMoving(bool function_enable)
{
	if(function_enable)
	{
		myGravity->Falling();
		myGravity->SetOnGround(false);
	}
	else
		myGravity->SetOnGround(true);
}
void SwordMan::DownAnimation()
{
	HeadDirection head_Direction = human->GetHeadDirection();
	if(head_Direction == Head_Left)
		picture_animation.OnMove(L_Jumping);
	if(head_Direction == Head_Right)
		picture_animation.OnMove(R_Jumping);
}
void SwordMan::AttackMoving()
{
	/*SkillSheet mySkillSheet =  human->MySkillSheet();
	//mySkillSheet.EnableSkill(Type_NoSkill);*/
}
void SwordMan::AttackAnimation()
{
	HeadDirection head_Direction = human->GetHeadDirection();
	if(head_Direction == Head_Left)
		picture_animation.OnMove(L_Attacking);
	if(head_Direction == Head_Right)
		picture_animation.OnMove(R_Attacking);
}

//void IRoleType::setMySize(int width,int height){}

void SwordMan::OnShow(int x,int y)
{
	picture_animation.SetTopLeft(x,y);//SIZE_X/2-50
	picture_animation.OnShow();
}
void SwordMan::LoadBitmap()
{
		int &x = human->GetX();
		int &y = human->GetY();
		char *RWalking[5] = {"Bitmaps/R/r_walk-1.bmp","Bitmaps/R/r_walk-2.bmp","Bitmaps/R/r_walk-3.bmp","Bitmaps/R/r_walk-2.bmp","Bitmaps/R/r_walk-1.bmp"};
		char *LWalking[5] = {"Bitmaps/L/l_walk-1.bmp","Bitmaps/L/l_walk-2.bmp","Bitmaps/L/l_walk-3.bmp","Bitmaps/L/l_walk-2.bmp","Bitmaps/L/l_walk-1.bmp"};
		char *RJumping[2] = {"Bitmaps/R/r_jump-1.bmp","Bitmaps/R/r_jump-2.bmp"};
		char *LJumping[2] = {"Bitmaps/L/l_jump-1.bmp","Bitmaps/L/l_jump-2.bmp"};
		char *RAttack[4] =  {"Bitmaps/R/r_attack-1.bmp","Bitmaps/R/r_attack-2.bmp","Bitmaps/R/r_attack-3.bmp","Bitmaps/R/r_attack-4.bmp"};
		char *LAttack[4] =  {"Bitmaps/L/l_attack-1.bmp","Bitmaps/L/l_attack-2.bmp","Bitmaps/L/l_attack-3.bmp","Bitmaps/L/l_attack-4.bmp"};
		
		picture_animation.LoadAnimation(R_Walking,RWalking,5,1);
		picture_animation.LoadAnimation(L_Walking,LWalking,5,1);
		picture_animation.LoadAnimation(R_Jumping,RJumping,2,1);
		picture_animation.LoadAnimation(L_Jumping,LJumping,2,1);
		picture_animation.LoadAnimation(R_Attacking,RAttack,4,0);
		picture_animation.LoadAnimation(L_Attacking,LAttack,4,0);
		picture_animation.StateInitialize();
		//setMySize(picture_animation->Width(),picture_animation->Height());
		picture_animation.SetTopLeft(x,y);
}
CharcterType SwordMan::MyType(){return Type_SwordMan;}
SwordMan::SwordMan(Human *human):IRoleType(human)
{
	int *y = &human->GetY();
	myGravity = new Gravity(y);
	//mySkill.AddSkill(Type_NoSkill,0);
}
SwordMan::~SwordMan()
{
	delete myGravity;
}
bool SwordMan::GetUpController(bool upMove)
{
	bool gothrough = false;
	if(myGravity->Dojump(upMove))
		gothrough = true;
	return gothrough;
}
bool SwordMan::GetDownController(bool downMove)
{
	bool gothrough = false;
	if(!myGravity->GetOnSky())
		gothrough = true;
	return gothrough;
}
bool SwordMan::GetLeftController(bool leftMove)
{
	bool gothrough = false;
	return leftMove;
}
bool SwordMan::GetRightController(bool rightMove)
{
	bool gothrough = false;
	return rightMove;
}

bool SwordMan::GetContinueAttack()
{
	Animax_act nowState = picture_animation.GetNowState();
	int picture_interval = picture_animation.GetCurrentAnitmationBitmap();
	if(nowState == L_Attacking ||nowState == R_Attacking)
		if(picture_interval <= 2)
			return true;
	return false;
}





Archer::Archer(Human *human):SwordMan(human)
{
	mySkill.AddSkill(Type_Arrow,0);
}
Archer::~Archer(){}
void Archer::LoadBitmap()
{
		int &x = human->GetX();
		int &y = human->GetY();
		char *RWalking[2] = {"Bitmaps/R/r_walk-1ar.bmp","Bitmaps/R/r_walk-2ar.bmp"};
		char *LWalking[2] = {"Bitmaps/L/l_walk-1ar.bmp","Bitmaps/L/l_walk-2ar.bmp"};
		char *RJumping[2] = {"Bitmaps/R/r_jump-1ar.bmp","Bitmaps/R/r_jump-2ar.bmp"};
		char *LJumping[2] = {"Bitmaps/L/l_jump-1ar.bmp","Bitmaps/L/l_jump-2ar.bmp"};
		char *RAttack[4] =  {"Bitmaps/R/r_attack-1ar.bmp","Bitmaps/R/r_attack-2ar.bmp","Bitmaps/R/r_attack-3ar.bmp","Bitmaps/R/r_attack-4ar.bmp"};
		char *LAttack[4] =  {"Bitmaps/L/l_attack-1ar.bmp","Bitmaps/L/l_attack-2ar.bmp","Bitmaps/L/l_attack-3ar.bmp","Bitmaps/L/l_attack-4ar.bmp"};

		picture_animation.LoadAnimation(R_Walking,RWalking,2,0);
		picture_animation.LoadAnimation(L_Walking,LWalking,2,0);
		picture_animation.LoadAnimation(R_Jumping,RJumping,2,0);
		picture_animation.LoadAnimation(L_Jumping,LJumping,2,0);
		picture_animation.LoadAnimation(R_Attacking,RAttack,4,0);
		picture_animation.LoadAnimation(L_Attacking,LAttack,4,0);
		picture_animation.StateInitialize();
		//setMySize(picture_animation->Width(),picture_animation->Height());
		picture_animation.SetTopLeft(x,y);
}

void Archer::AttackMoving()
{
	mySkill.EnableSkill(Type_Arrow);
}

CharcterType Archer::MyType()
{
	return Type_Archer;
}




Mage::Mage(Human *human):SwordMan(human)
{
	mySkill.AddSkill(Type_MagicBall,0);
}
Mage::~Mage(){}
void Mage::LoadBitmap()
{
		int &x = human->GetX();
		int &y = human->GetY();
		char *RWalking[4] = {"Bitmaps/R/r_walk-1mg.bmp","Bitmaps/R/r_walk-2mg.bmp","Bitmaps/R/r_walk-3mg.bmp","Bitmaps/R/r_walk-4mg.bmp"};
		char *LWalking[4] = {"Bitmaps/L/l_walk-1mg.bmp","Bitmaps/L/l_walk-2mg.bmp","Bitmaps/L/l_walk-3mg.bmp","Bitmaps/L/l_walk-4mg.bmp"};
		char *RJumping[2] = {"Bitmaps/R/r_jump-1mg.bmp","Bitmaps/R/r_jump-2mg.bmp"};
		char *LJumping[2] = {"Bitmaps/L/l_jump-1mg.bmp","Bitmaps/L/l_jump-2mg.bmp"};
		char *RAttack[3] =  {"Bitmaps/R/r_attack-1mg.bmp","Bitmaps/R/r_attack-2mg.bmp","Bitmaps/R/r_attack-3mg.bmp"};
		char *LAttack[3] =  {"Bitmaps/L/l_attack-1mg.bmp","Bitmaps/L/l_attack-2mg.bmp","Bitmaps/L/l_attack-3mg.bmp"};

		picture_animation.LoadAnimation(R_Walking,RWalking,4,1);
		picture_animation.LoadAnimation(L_Walking,LWalking,4,1);
		picture_animation.LoadAnimation(R_Jumping,RJumping,2,1);
		picture_animation.LoadAnimation(L_Jumping,LJumping,2,1);
		picture_animation.LoadAnimation(R_Attacking,RAttack,3,1);
		picture_animation.LoadAnimation(L_Attacking,LAttack,3,1);
		picture_animation.StateInitialize();
		//setMySize(picture_animation->Width(),picture_animation->Height());
		picture_animation.SetTopLeft(x,y);
}

void Mage::AttackMoving()
{
	mySkill.EnableSkill(Type_MagicBall);
}

CharcterType Mage::MyType()
{
	return Type_Mage;
}

bool Mage::GetContinueAttack()
{
	Animax_act nowState = picture_animation.GetNowState();
	int picture_interval = picture_animation.GetCurrentAnitmationBitmap();
	if(nowState == L_Attacking ||nowState == R_Attacking)
		if(picture_interval <= 1)
			return true;
	return false;
}








MushRoom::MushRoom(Human *human):SwordMan(human)
{
	mySkill.AddSkill(Type_NoSkill,0);
}
MushRoom::~MushRoom(){}
void MushRoom::LoadBitmap()
{
		int &x = human->GetX();
		int &y = human->GetY();
		char *RWalking[4] = {"Bitmaps/r_mushroom.bmp","Bitmaps/l_mushroom.bmp"};
		char *LWalking[4] = {"Bitmaps/l_mushroom.bmp","Bitmaps/r_mushroom.bmp"};
/*		char *RJumping[2] = {"Bitmaps/R/r_jump-1mg.bmp","Bitmaps/R/r_jump-2mg.bmp"};
		char *LJumping[2] = {"Bitmaps/L/l_jump-1mg.bmp","Bitmaps/L/l_jump-2mg.bmp"};
		char *RAttack[3] =  {"Bitmaps/R/r_attack-1mg.bmp","Bitmaps/R/r_attack-2mg.bmp","Bitmaps/R/r_attack-3mg.bmp"};
		char *LAttack[3] =  {"Bitmaps/L/l_attack-1mg.bmp","Bitmaps/L/l_attack-2mg.bmp","Bitmaps/L/l_attack-3mg.bmp"};
*/
		picture_animation.LoadAnimation(R_Walking,RWalking,2,0);
		picture_animation.LoadAnimation(L_Walking,LWalking,2,0);
		picture_animation.LoadAnimation(R_Jumping,RWalking,2,0);
		picture_animation.LoadAnimation(L_Jumping,LWalking,2,0);
		picture_animation.LoadAnimation(R_Attacking,RWalking,2,0);
		picture_animation.LoadAnimation(L_Attacking,LWalking,2,0);
		picture_animation.StateInitialize();
		//setMySize(picture_animation->Width(),picture_animation->Height());
		picture_animation.SetTopLeft(x,y);
}

void MushRoom::AttackMoving()
{
	mySkill.EnableSkill(Type_NoSkill);
}

CharcterType MushRoom::MyType()
{
	return Type_MushRoom;
}

bool MushRoom::GetContinueAttack()
{
	return true;
}