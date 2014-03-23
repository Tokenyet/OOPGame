#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "stdafx.h"
#include <ddraw.h>
#include "Human.h"
#include <vector>

class Movement_System
{
private:
	Human *charcter;
	vector<Human*> objects;
	void charcter_Restriction_OnMove();
public:
	Movement_System();
	~Movement_System();
	void OnShow();
	void OnMove();
	void LoadObjects(vector<Human*>);
	void LoadCharcter(Human*);
	void KeyUpUpdate(UINT);
	void KeyDownUpdate(UINT);
};


#endif