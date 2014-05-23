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
		SkillSheet skillSheet = charcter->MySkillSheet();
		Skill_Type typeOfSkill =  skillSheet.UsedSkill();
		int damage = skillSheet.UsedSkillDamage();

		if(attacking)
		{
			if(delayTime != 0)
				delayTime = (delayTime + 1)%22;
			if(delayTime == 0)
			{
				ArrowBox* arrow = skillPower(typeOfSkill,damage);
				if(arrow != NULL)
					arrowBoxes->push_back(arrow);
			}
		}
		else
			delayTime = 0;
	}
	ArrowBox* SkillSets::skillPower(Skill_Type typeOfSkill,int damage)
	{
		delayTime = 1;
		int delta = charcter->GetDistanceFromOriginX();
		int x = charcter->GetX() - delta;
		int y = charcter->GetY() + 30;
		HeadDirection head = charcter->GetHeadDirection();

		switch(typeOfSkill)
		{
			case Type_NoSkill:
				return NULL;
				break;
			case Type_Arrow:
				return new ArrowBox(x,y,head);
				break;
		}
		return NULL;
	}