#ifndef SCROLL_SYSTEM_H
#define SCROLL_SYSTEM_H
#include "StdAfx.h"
#include "Human.h"
#include "IPerform.h"
#include "Map.h"
#include "ScreenMap.h"
#include <vector>

class Scroll_System
{
private:
	vector<Map> maps;
	vector<IPerform*> locations;
	ScreenMap screenMap;
	Human* charcter;
	int windows_X,windows_Y;
	void Object_Sync_Move();
	bool upMove,downMove,rightMove,leftMove;
	void mapSettingInitialize();
	bool Check_Map_OutOfHeight();
public:
	Scroll_System();
	void Initialize(vector<IPerform*> locations);
	void SetCharcter(Human *mainCharcter);
	void SetWindowsSize(int windows_X,int windows_Y);
	void AddObject(IPerform *things);
	void AddObject(vector<IPerform*> things);
	void KeyDownUpdate(UINT keyin);
	void KeyUpUpdate(UINT keyin);
	void OnShowMap();
	void OnMove();
};
#endif