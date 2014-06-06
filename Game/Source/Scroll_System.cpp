#include "stdafx.h"
//#include "Human.h"
#include "IPerform.h"
#include "Map.h"
#include "ScreenMap.h"
#include "Scroll_System.h"
#include <vector>


	Scroll_System::Scroll_System()
	{
		upMove = downMove = rightMove = leftMove = false;
	}
	Scroll_System::~Scroll_System()
	{
	}
	void Scroll_System::Initialize(vector<IPerform*> *locations)
	{
		maps.clear();
		this->locations = locations;
		mapSettingInitialize("Bitmaps/bg2-1.bmp");
		screenMap.Initialization(maps);
	}
	void Scroll_System::ReInitialize(vector<IPerform*> *locations)
	{
		this->locations = locations;
	}

	void Scroll_System::mapSettingInitialize(char* MapPath)//"Bitmaps/bg2-1.bmp"
	{
		Map map,map2,map3;
		map.Initialize((int)SIZE_X,(int)SIZE_Y,MapPath);
		map2.Initialize((int)SIZE_X,(int)SIZE_Y,MapPath);
		map3.Initialize((int)SIZE_X,(int)SIZE_Y,MapPath);
		maps.push_back(map);
		maps.push_back(map2);
		maps.push_back(map3);
	}
	void Scroll_System::ChangeMap(char* MapPath)
	{
		maps.clear();
		mapSettingInitialize(MapPath);
	}

	void Scroll_System::SetCharcter(Human *mainCharcter)
	{
		charcter = mainCharcter;
		screenMap.SyncCharcterPoisition(&charcter->GetX(),&charcter->GetY());
	}
	void Scroll_System::SetWindowsSize(int windows_X,int windows_Y)
	{
		this->windows_X = windows_X;
		this->windows_Y = windows_Y;
	}
	void Scroll_System::AddObject(IPerform *things)
	{
		locations->push_back(things);
	}
	void Scroll_System::DelObject(IPerform *things)
	{
		for(size_t i=0;i<locations->size();i++)
			if((*locations)[i]==things)
				locations->erase(locations->begin()+i);
	}

	void Scroll_System::DelEnemy(Enemy *enemy)
	{
		for(size_t i=0;i<enemys->size();i++)
			if((*enemys)[i]==enemy)
				enemys->erase(enemys->begin()+i);
	}


	void Scroll_System::AddObject(vector<IPerform*> things)
	{
		for(size_t i = 0;i<things.size();i++)
			locations->push_back(things[i]);
	}
	void Scroll_System::AddEnemy(Enemy *enemy)
	{
		enemys->push_back(enemy);
	}

	void Scroll_System::LoadEnemy(vector<Enemy*> *enemys)
	{
		this->enemys = enemys;
	}

	void Scroll_System::AddEnemy(vector<Enemy*> *enemys)
	{
		for(size_t i = 0;i<enemys->size();i++)
			this->enemys->push_back((*enemys)[i]);
	}

	void Scroll_System::LoadArrows(vector<ArrowBox*>* arrowBoxes)
	{
		this->arrowBoxes = arrowBoxes;
	}

	void Scroll_System::KeyDownUpdate(UINT keyin)
	{
		const char KEY_LEFT  = 0x25; // keyboard左箭頭
		const char KEY_UP    = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN  = 0x28; // keyboard下箭頭
		if(keyin == KEY_LEFT)
			leftMove = true;
		if(keyin == KEY_UP)
			upMove = true;
		if(keyin == KEY_DOWN)
			downMove = true;
		if(keyin == KEY_RIGHT)
			rightMove = true;
		screenMap.SetKeyDownControl(keyin);
	}
	void Scroll_System::KeyUpUpdate(UINT keyin)
	{
		const char KEY_LEFT  = 0x25; // keyboard左箭頭
		const char KEY_UP    = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN  = 0x28; // keyboard下箭頭
		if(keyin == KEY_LEFT)
			leftMove = false;
		if(keyin == KEY_UP)
			upMove = false;
		if(keyin == KEY_DOWN)
			downMove = false;
		if(keyin == KEY_RIGHT)
			rightMove = false;
		screenMap.SetKeyUpControl(keyin);
	}
	void Scroll_System::OnShowMap()
	{
		screenMap.OnShow();
	}
	void Scroll_System::OnMove()
	{
		enemy_Sync_Move();
		object_Sync_Move();
		arrow_Sync_Move();
		screenMap.SetCharcterUpRestriction(charcter->getUpRestriction());
		screenMap.SetCharcterDownRestriction(charcter->getDownRestriction());
		screenMap.OnMove();
	}
	void Scroll_System::object_Sync_Move()
	{
		for(size_t i = 0;i<locations->size();i++)
		{
		/*if (leftMove)
			object_Left(locations[i]);
		if (rightMove)
			object_Right(locations[i]);*/
		if (upMove)
			object_Up((*locations)[i]);
		if (!upMove)
			object_Down((*locations)[i]);
		object_Right((*locations)[i]);
		(*locations)[i] ->OnMove();
		}
	}

	void Scroll_System::enemy_Sync_Move()
	{
		bool right_restriction = charcter->getRightRestriction();
		bool left_restriction = charcter->getLeftRestriction();
		for(size_t i = 0;i<enemys->size();i++)
		{
		if (leftMove&&!left_restriction)
			(*enemys)[i]->GetX() += 5;
		if (rightMove&&!right_restriction)
			(*enemys)[i]->GetX() -= 5;
		if (upMove)
			(*enemys)[i]-> GetY()++;
		if (!upMove)
			(*enemys)[i] -> GetY()--;
		}
	}

	void Scroll_System::arrow_Sync_Move()
	{
		bool right_restriction = charcter->getRightRestriction();
		bool left_restriction = charcter->getLeftRestriction();
		for(size_t i = 0;i<arrowBoxes->size();i++)
		{
		if (leftMove&&!left_restriction)
			(*arrowBoxes)[i]->GetX() += 5;
		if (rightMove&&!right_restriction)
			(*arrowBoxes)[i]->GetX() -= 5;
		if (upMove)
			(*arrowBoxes)[i]-> GetY()++;
		if (!upMove)
			(*arrowBoxes)[i] -> GetY()--;
		}
	}


	void Scroll_System::object_Up(IPerform* object)
	{
		if(!screenMap.GetTopRestriction())
			object -> GetY()++;
	}
	void Scroll_System::object_Down(IPerform* object)
	{
		if(!screenMap.GetBottomRestriction())
			object  -> GetY()--;
	}
	void Scroll_System::object_Right(IPerform* object)
	{
		//int screenMap_x = screenMap.TestMap_X();//必須在人物之後更新地圖與物件移動
		object  -> GetX() = object->GetOriginX() - charcter->GetDistanceFromOriginX();
	}
	void Scroll_System::object_Left(IPerform* object)
	{
		object  -> GetX() = object->GetOriginX() - charcter->GetDistanceFromOriginX();
	}
