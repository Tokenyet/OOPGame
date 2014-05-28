#include "StdAfx.h"
#include "Charcter.h"
#include "audio.h"
#include "IRoleType.h"


	Charcter::Charcter():Human(SIZE_X/2-50,0)
	{
		//myGravity = new Gravity(&GetY());
		myType = new SwordMan(this);
		head_Direction = Head_Right;
		upMove = downMove = rightMove = leftMove = false;
		upRestriction=downRestriction=rightRestriction=leftRestriction = false;
		//g = 10;
	}
	Charcter::~Charcter()
	{
		delete myType;
		//delete myGravity;
	}
	void Charcter::OnMove()
	{
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
		myRect.SetOriginRectangle(SIZE_X/2-50,GetY(),GetWidth(),GetHeight(),5);
	}
	void Charcter::LoadBitmap()
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
	void Charcter::OnShow()
	{
		myType->OnShow(SIZE_X/2-50,GetY());
		/*picture_animation->SetTopLeft(SIZE_X/2-50,GetY());//SIZE_X/2-50
		picture_animation->OnShow();*/
	}
	void Charcter::leftMoving()
	{
		rightRestriction = false;
		int speed = 5;
		if(getLeftRestriction())
		{
			if(!(SIZE_X/2-50 <= leftBoundedValue)) // SIZE_X/2-50 <= leftBoundedValue
				myType->LeftMoving();
		}
		else
			myType->LeftMoving();

			/*else
				x -= speed;*/
	}
	void Charcter::rightMoving()
	{

		int speed = 5;
		int width = myType->GetWidth();//picture_animation->Width();
		if(getRightRestriction())
		{
			if(!(SIZE_X/2-50 + width>= rightBoundedValue))//SIZE_X/2-50 + width >= rightBoundedValue
				myType->RightMoving();
		}
		else
			myType->RightMoving();

			/*else
				x += speed;*/
	}
	void Charcter::upMoving()
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
	void Charcter::downMoving()
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
	void Charcter::attackMoving()
	{
		myType->AttackMoving();
		//mySkill.EnableSkill(mySkill.UsedSkill);
	}
	void Charcter::leftAnimation()
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
	void Charcter::rightAnimation()
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
	void Charcter::upAnimation()
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
	void Charcter::downAnimation()
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
	void Charcter::attackAnimation()
	{
		myType->AttackAnimation();
		/*
			if(head_Direction == Head_Left)
				picture_animation->OnMove(L_Attacking);
			if(head_Direction == Head_Right)
				picture_animation->OnMove(R_Attacking);*/
	}

	void Charcter::AddThing(Thing *Item)
	{
		if(Item->GetName() == "New")
		{
			delete myType;
			myType = new Archer(this);
			myType->LoadBitmapA();
		}
		Item->MakeOwnerBy(this);
		setMySize(myType->GetWidth(),myType->GetHeight());
	}

	bool Charcter::GetAttacking()
	{
		return attackMove;
	}
	bool Charcter::GetRestartGame()
	{
		if(GetY() > SIZE_Y)
			return true;
		return false;
	}

	int Charcter::MyType()
	{
		return myType->MyType();
	}


	SkillSheet Charcter::MySkillSheet()
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