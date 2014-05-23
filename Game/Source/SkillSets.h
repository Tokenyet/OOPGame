#ifndef SKILLSETS_H
#define SKILLSETS_H
#include "Human.h"
#include "ArrowBox.h"

class SkillSets
{
private:
	Human *charcter;
	vector<ArrowBox*>* arrowBoxes;
	int delayTime;
	ArrowBox* skillPower(Skill_Type,int);
public:
	SkillSets();
	void Initialization(Human* charcter,vector<ArrowBox*>* arrowBoxes);
	void OnMove();

};
#endif
