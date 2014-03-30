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
	void Scroll_System::Initialize(vector<IPerform*> locations)
	{
		this->locations = locations;
		mapSettingInitialize();
		screenMap.Initialization(maps);
	}
	void Scroll_System::mapSettingInitialize()
	{
		Map map,map2,map3;
		map.Initialize((int)SIZE_X,(int)SIZE_Y,"Bitmaps/bg2-1.bmp");
		map2.Initialize((int)SIZE_X,(int)SIZE_Y,"Bitmaps/bg2-1.bmp");
		map3.Initialize((int)SIZE_X,(int)SIZE_Y,"Bitmaps/bg2-1.bmp");
		maps.push_back(map);
		maps.push_back(map2);
		maps.push_back(map3);
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
		locations.push_back(things);
	}
	void Scroll_System::DelObject(IPerform *things)
	{
		for(size_t i=0;i<locations.size();i++)
			if(locations[i]==things)
				locations.erase(locations.begin()+i);
	}

	void Scroll_System::AddObject(vector<IPerform*> things)
	{
		for(size_t i = 0;i<things.size();i++)
			locations.push_back(things[i]);
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
		object_Sync_Move();
		screenMap.SetCharcterUpRestriction(charcter->getUpRestriction());
		screenMap.SetCharcterDownRestriction(charcter->getDownRestriction());
		screenMap.OnMove();
	}
	void Scroll_System::object_Sync_Move()
	{
		for(size_t i = 0;i<locations.size();i++)
		{
		/*if (leftMove)
			object_Left(locations[i]);
		if (rightMove)
			object_Right(locations[i]);*/
		if (upMove)
			object_Up(locations[i]);
		if (downMove)
			object_Down(locations[i]);
		object_Right(locations[i]);
		locations[i] ->OnMove();
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
