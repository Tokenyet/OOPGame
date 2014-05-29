#ifndef SKILLSHEET_H
#define SKILLSHEET_H
#include <ddraw.h>
#include "gamelib.h"
#include "Animation.h"

enum Skill_Type
{
	Type_NoSkill = 0,
	Type_Arrow = 1,
	Type_MagicBall = 2,
};





class SkillSheet
{
private:
	int ability_amount;
	bool usingSkill;
	Skill_Type nowSkill;
	map<Skill_Type,int> mySkillDamage;
public:
	SkillSheet();
	~SkillSheet();
	void AddSkill(Skill_Type,int damage);
	void EnableSkill(Skill_Type);
	void DisableSkill();
	Skill_Type UsedSkill();
	int UsedSkillDamage();


};
#endif

