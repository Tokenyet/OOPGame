#include "StdAfx.h"
#include "Movement_System.h"

Movement_System::Movement_System(){}
Movement_System::~Movement_System(){}
void Movement_System::OnShow(){charcter->OnShow();}
void Movement_System::OnMove()
{
	charcter_Restriction_OnMove();
}
void Movement_System::LoadObjects(vector<Human*> objects){this->objects = objects;}
void Movement_System::LoadCharcter(Human *charcter){ this->charcter = charcter;}
void Movement_System::KeyUpUpdate(UINT keyin){ this->charcter->KeyUpDetect(keyin);}
void Movement_System::KeyDownUpdate(UINT keyin){ this->charcter->KeyDownDetect(keyin);}
void Movement_System::charcter_Restriction_OnMove()
{
		charcter->OnMove();
}