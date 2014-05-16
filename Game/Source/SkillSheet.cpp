#include "StdAfx.h"
#include "SkillSheet.h"

SkillSheet::SkillSheet()
{
	ability_amount = 0;
	nowSkill = Type_NoSkill;
	mySkillDamage[Type_NoSkill] = 0;
}

SkillSheet::~SkillSheet()
{

}


void SkillSheet::AddSkill(Skill_Type skillType,int damage)
{
	mySkillDamage[skillType] = damage;
	ability_amount = mySkillDamage.size();
}

void SkillSheet::EnableSkill(Skill_Type skillType)
{
	nowSkill = skillType;
}

void SkillSheet::DisableSkill()
{
	nowSkill = Type_NoSkill;
}


Skill_Type SkillSheet::UsedSkill()
{
	return nowSkill;
}

int SkillSheet::UsedSkillDamage()
{
	return mySkillDamage[nowSkill];
}