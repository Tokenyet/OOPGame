#include "StdAfx.h"
#include "SkillSets.h"
#include "IRoleType.h"

	SkillSets::SkillSets()
	{
		delayTime= 0;
	}

	void SkillSets::Initialization(Human* charcter,vector<ArrowBox*>* arrowBoxes)
	{
		this->charcter = charcter;
		this->arrowBoxes = arrowBoxes;
	}

	void SkillSets::OnMove()
	{
		int CD = 50;
		bool attacking = charcter->GetAttacking();
		if(charcter->MyType() == Type_Archer&&attacking)
		{
			if(delayTime != 0)
				delayTime = (delayTime + 1)%22;
			if(delayTime == 0)
				arrowBoxes->push_back(skillPower());
		}
		else
			delayTime = 0;
	}
	ArrowBox* SkillSets::skillPower()
	{
		delayTime = 1;
		int delta = charcter->GetDistanceFromOriginX();
		int x = charcter->GetX() - delta;
		int y = charcter->GetY() + 30;
		HeadDirection head = charcter->GetHeadDirection();
		return new ArrowBox(x,y,head);
	}