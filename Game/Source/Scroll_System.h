#ifndef SCROLL_SYSTEM_H
#define SCROLL_SYSTEM_H
#include "StdAfx.h"
#include "Human.h"
#include "IPerform.h"
#include "Map.h"
#include "ScreenMap.h"
#include <vector>
#include "Enemy.h"
#include "ArrowBox.h"
class Scroll_System
{
private:
	vector<Map> maps;
	vector<IPerform*> *locations;
	vector<Enemy*> *enemys;
	vector<ArrowBox*>* arrowBoxes;
	ScreenMap screenMap;
	Human* charcter;
	int windows_X,windows_Y;
	void object_Sync_Move();
	void enemy_Sync_Move();
	void arrow_Sync_Move();
	bool upMove,downMove,rightMove,leftMove;
	void mapSettingInitialize();
	void object_Up(IPerform*);
	void object_Down(IPerform*);
	void object_Right(IPerform*);
	void object_Left(IPerform*);
public:
	Scroll_System();
	~Scroll_System();
	void Initialize(vector<IPerform*>* locations);
	void SetCharcter(Human *mainCharcter);
	void SetWindowsSize(int windows_X,int windows_Y);
	void AddObject(IPerform *things);
	void DelObject(IPerform *things);
	void AddObject(vector<IPerform*> things);
	void AddEnemy(Enemy *enemy);
	void DelEnemy(Enemy *enemy);
	void LoadEnemy(vector<Enemy*> *enemys);
	void AddEnemy(vector<Enemy*> *enemys);
	void LoadArrows(vector<ArrowBox*>* arrowBoxes);
	void KeyDownUpdate(UINT keyin);
	void KeyUpUpdate(UINT keyin);
	void OnShowMap();
	void OnMove();
};
#endif