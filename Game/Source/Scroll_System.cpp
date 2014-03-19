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
		Object_Sync_Move();
		screenMap.OnMove();
	}
	void Scroll_System::Object_Sync_Move()
	{
		for(size_t i = 0;i<locations.size();i++)
		{
		if (leftMove)
			locations[i] -> GetX()+=10;
		if (rightMove)
			locations[i]  -> GetX()-=10;
		if (upMove)
			locations[i]  -> GetY()++;
		if (downMove)
			locations[i]  -> GetY()--;
		locations[i] ->OnMove();
		}
	}
