#include "StdAfx.h"
#include "Enemy.h"
#include "audio.h"
#include "IRoleType.h"


	Enemy::Enemy(int initial_X,int initial_Y,CharcterType TypeOfCharcter):Human(initial_X,initial_Y)
	{
		//myGravity = new Gravity(&GetY());
		myType = GetMyType(TypeOfCharcter);
		head_Direction = Head_Right;
		upMove = downMove = rightMove = leftMove = false;
		upRestriction=downRestriction=rightRestriction=leftRestriction = false;
		leftMove =true;
		//g = 10;
	}
	Enemy::~Enemy()
	{
		delete myType;
		//delete myGravity;
	}
	IRoleType* Enemy::GetMyType(CharcterType TypeOfCharcter)
	{
		switch(TypeOfCharcter)
		{
		case Type_MushRoom:
			return new MushRoom(this);
		case Type_Enemy1:
			return new Enemy1(this);
		case Type_Enemy2:
			return new Enemy2(this);
		case Type_Enemy3:
			return new Enemy3(this);
		case Type_Enemy4:
			return new Enemy4(this);
		case Type_Enemy5:
			return new Enemy5(this);
		case Type_Enemy6:
			return new Enemy6(this);
		case Type_Enemy7:
			return new Enemy7(this);
		case Type_Enemy8:
			return new Enemy8(this);
		default:
			return new IRoleType(this);
		}
		ASSERT(0);
		return NULL;
	}
	void Enemy::MovingAI()
	{
		if(getLeftRestriction())
		{
			head_Direction = Head_Right;
			rightMove = true;
			leftMove = false;
		}
		if(getRightRestriction())
		{
			head_Direction = Head_Left;
			rightMove = false;
			leftMove = true;
		}
	}


	void Enemy::OnMove()
	{
		MovingAI();
		bool LeftRestricion =  myType->GetLeftController(leftMove);
		bool RightRestricion =  myType->GetRightController(rightMove);
		bool UpRestricion =  myType->GetUpController(upMove);
		bool DownRestricion =  myType->GetDownController(downMove);
		
		if(myType->GetContinueAttack())
			attackMove = true;

		if (LeftRestricion)
		{
			leftMoving();
			leftAnimation();
		}
		if (RightRestricion)
		{
			rightMoving();
			rightAnimation();
		}
		if(UpRestricion)
		{
			upMoving();
			upAnimation();
		}
		if(DownRestricion)
		{
			downMoving();
			downAnimation();
		}
		/*
		if (myGravity->Dojump(upMove))
		{
			upMoving();
			upAnimation();
		}
		if (!myGravity->GetOnSky())
		{
			downMoving();
			downAnimation();
		}*/
		if(attackMove)
		{
			attackMoving();
			attackAnimation();
			if(!myType->GetContinueAttack())
			attackMove = false;
		}



		if(!leftMove&&!rightMove&&!upMove&&!downMove&&!myType->GetContinueAttack())
		{
			myType->AnimationReset();
			if(head_Direction == Head_Left)
				myType->LeftAnimation();
			else
				myType->RightAnimation();
		}
		//myRect.SetOriginRectangle(SIZE_X/2-50,GetY(),picture_animation->Width(),picture_animation->Height(),5);//SIZE_X/2-50
		myRect.SetOriginRectangle(GetX(),GetY(),GetWidth(),GetHeight(),5);
	}
	void Enemy::LoadBitmap()
	{
		/*
		char *RWalking[5] = {"Bitmaps/R/r_walk-1.bmp","Bitmaps/R/r_walk-2.bmp","Bitmaps/R/r_walk-3.bmp","Bitmaps/R/r_walk-2.bmp","Bitmaps/R/r_walk-1.bmp"};
		char *LWalking[5] = {"Bitmaps/L/l_walk-1.bmp","Bitmaps/L/l_walk-2.bmp","Bitmaps/L/l_walk-3.bmp","Bitmaps/L/l_walk-2.bmp","Bitmaps/L/l_walk-1.bmp"};
		char *RJumping[2] = {"Bitmaps/R/r_jump-1.bmp","Bitmaps/R/r_jump-2.bmp"};
		char *LJumping[2] = {"Bitmaps/L/l_jump-1.bmp","Bitmaps/L/l_jump-2.bmp"};
		char *RAttack[4] =  {"Bitmaps/R/r_attack-1.bmp","Bitmaps/R/r_attack-2.bmp","Bitmaps/R/r_attack-3.bmp","Bitmaps/R/r_attack-4.bmp"};
		char *LAttack[4] =  {"Bitmaps/L/l_attack-1.bmp","Bitmaps/L/l_attack-2.bmp","Bitmaps/L/l_attack-3.bmp","Bitmaps/L/l_attack-4.bmp"};
		
		picture_animation->LoadAnimation(R_Walking,RWalking,5,1);
		picture_animation->LoadAnimation(L_Walking,LWalking,5,1);
		picture_animation->LoadAnimation(R_Jumping,RJumping,2,1);
		picture_animation->LoadAnimation(L_Jumping,LJumping,2,1);
		picture_animation->LoadAnimation(R_Attacking,RAttack,4,0);
		picture_animation->LoadAnimation(L_Attacking,LAttack,4,0);
		picture_animation->StateInitialize();
		setMySize(picture_animation->Width(),picture_animation->Height());
		picture_animation->SetTopLeft(GetX(),GetY());*/
		myType->LoadBitmapA();
		setMySize(myType->GetWidth(),myType->GetHeight());
	}
	void Enemy::OnShow()
	{
		myType->OnShow(GetX(),GetY());
		MessageShow(GetX(),GetY()-40,health);
		/*picture_animation->SetTopLeft(SIZE_X/2-50,GetY());//SIZE_X/2-50
		picture_animation->OnShow();*/
	}
	void Enemy::leftMoving()
	{
		rightRestriction = false;
		int speed = 5;
		if(getLeftRestriction())
		{
			if(!(GetX() <= leftBoundedValue)) // SIZE_X/2-50 <= leftBoundedValue
				myType->LeftMoving();
		}
		else
			myType->LeftMoving();

			/*else
				x -= speed;*/
	}
	void Enemy::rightMoving()
	{

		int speed = 5;
		int width = myType->GetWidth();//picture_animation->Width();
		if(getRightRestriction())
		{
			if(!(GetX() + width>= rightBoundedValue))//SIZE_X/2-50 + width >= rightBoundedValue
				myType->RightMoving();
		}
		else
			myType->RightMoving();

			/*else
				x += speed;*/
	}
	void Enemy::upMoving()
	{
		if(getUpRestriction())
		{
			if(!(GetY() <= upBoundedValue))
			{
				myType->UpMoving(true);
				//myGravity->Jumping();
			}
			if(GetY() <= upBoundedValue)
			{
				myType->UpMoving(false);
				/*myGravity->SetOnSky(false);
				myGravity->SetKeepUpMove(false);*/
			}
		}
		else
		{
			myType->UpMoving(true);
			//myGravity->Jumping();
		}
	}
	void Enemy::downMoving()
	{
		//int height = picture_animation->Height();
		int height = GetHeight();
		if(getDownRestriction())
		{
			if(!(GetY() + height > downBoundedValue))
			{
				myType->DownMoving(true);
				/*myGravity->Falling();
				myGravity->SetOnGround(false);*/
			}
			if((GetY() + height >= downBoundedValue))
			{
				myType->DownMoving(false);
				GetY() = downBoundedValue - height;
				//myGravity->SetOnGround(true);
			}
		}
		else
		{
			myType->DownMoving(true);
				/*myGravity->Falling();
				myGravity->SetOnGround(false);*/
		}
	}
	void Enemy::attackMoving()
	{
		myType->AttackMoving();
		//mySkill.EnableSkill(mySkill.UsedSkill);
	}
	void Enemy::leftAnimation()
	{	
		bool gothrough = true;

		if(attackMove)
			gothrough = false;
		if(!rightMove&&gothrough)
		{
			head_Direction = Head_Left;
			//picture_animation->OnMove(L_Walking);
			myType->LeftAnimation();
		}
	}
	void Enemy::rightAnimation()
	{
		bool gothrough = true;
		if(attackMove)
			gothrough = false;
		if(!leftMove&&gothrough)
		{
			head_Direction = Head_Right;
			//picture_animation->OnMove(R_Walking);
			myType->RightAnimation();
		}
	}
	void Enemy::upAnimation()
	{
		bool gothrough = true;
		if(attackMove)
			gothrough = false;
		/*if(head_Direction == Head_Left&&gothrough)
			picture_animation->OnMove(L_Jumping);
		if(head_Direction == Head_Right&&gothrough)
			picture_animation->OnMove(R_Jumping);*/
		if(gothrough)
		myType->UpAnimation();
	}
	void Enemy::downAnimation()
	{
		bool isOnGround = getDownRestriction();//myGravity->GetOnGround();
		bool gothrough = true;
		if(attackMove)
			gothrough = false;
		if(gothrough)
		{
			if(!isOnGround)
			{
				myType->DownAnimation();/*
				if(head_Direction == Head_Left)
					picture_animation->OnMove(L_Jumping);
				if(head_Direction == Head_Right)
					picture_animation->OnMove(R_Jumping);*/
			}
			else
			{
				bool check = false;
				if(isOnGround&&!attackMove)
					check = true;
				if(head_Direction == Head_Left&&check)
				{
					myType->LeftAnimation();
				//	picture_animation->OnMove(L_Walking);
				}
				if(head_Direction == Head_Right&&check)
				{
					myType->RightAnimation();
					//picture_animation->OnMove(R_Walking);
				}
			}
		}
	}
	void Enemy::attackAnimation()
	{
		myType->AttackAnimation();
		/*
			if(head_Direction == Head_Left)
				picture_animation->OnMove(L_Attacking);
			if(head_Direction == Head_Right)
				picture_animation->OnMove(R_Attacking);*/
	}

	void Enemy::AddThing(Thing *Item)
	{
	/*	if(Item->GetName() == "New")
		{
			delete myType;
			myType = new Archer(this);
			myType->LoadBitmapA();
		}*/
		Item->MakeOwnerBy(this);
		setMySize(myType->GetWidth(),myType->GetHeight());
	}

	bool Enemy::GetAttacking()
	{
		return attackMove;
	}
	bool Enemy::GetRestartGame()
	{
		if(GetY() > SIZE_Y)
			return true;
		return false;
	}

	int Enemy::MyType()
	{
		return myType->MyType();
	}


	SkillSheet Enemy::MySkillSheet()
	{
		/*
		mySkill.AddSkill(Type_NoSkill,0);
		if(myType->MyType() == Type_Archer)
		{
			mySkill.AddSkill(Type_Arrow,10);
			mySkill.EnableSkill(Type_Arrow);
		}*/
		return 	myType->MySkillSheet();;
	}


	Enemy_OverWall::Enemy_OverWall(int initial_X,int initial_Y,CharcterType TypeOfCharcter):Enemy(initial_X,initial_Y,TypeOfCharcter){}
	Enemy_OverWall::~Enemy_OverWall(){}
	void Enemy_OverWall::MovingAI()
	{
		if(getLeftRestriction())
		{
			head_Direction = Head_Right;
			upMove = true;
			rightMove = true;
			leftMove = false;
		}
		else if(getRightRestriction())
		{
			head_Direction = Head_Left;
			upMove = true;
			rightMove = false;
			leftMove = true;
		}
		else
			upMove = false;
	}