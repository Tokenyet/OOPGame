#include "stdafx.h"
#include "ScreenMap.h"
#include "Map.h"

	ScreenMap::ScreenMap()
	{
		offset_Heigth = 0;
	}
	ScreenMap::~ScreenMap(){}
	void ScreenMap::Initialization(vector<Map> &maps)
	{
		AddMap(maps);
		Reset();

	}
	void ScreenMap::AddMap(vector<Map> &maps)
	{
		for(size_t i =0;i<maps.size();i++)
			(this->maps).push_back(&maps[i]);
		
	}
	void ScreenMap::AddMap(Map* map)
	{
		maps.push_back(map);
	}
	void ScreenMap::OnMove()
	{
		int restriction_value = currentMap->GetY();
		if (leftMove)
		{
			pastMap -> GetX()+=10;
			currentMap->GetX()+=10;
			nextMap->GetX()+=10;
		}	
		if (rightMove)
		{
			pastMap -> GetX()-=10;
			currentMap->GetX()-=10;
			nextMap->GetX()-=10;
		}
		if (upMove&& restriction_value < 0)
		{
			pastMap -> GetY()++;
			currentMap->GetY()++;
			nextMap->GetY()++;
			offset_Heigth ++;
		}
		if (downMove && restriction_value > Different_Map_HeigthOffset(0))
		{
			pastMap -> GetY()--;
			currentMap->GetY()--;
			nextMap->GetY()--;
			offset_Heigth--;
		}
		currentMap->SetMapLocation(currentMap->GetX(),currentMap->GetY());
		nextMap->SetMapLocation(nextMap->GetX(),nextMap->GetY());
		pastMap->SetMapLocation(pastMap->GetX(),pastMap->GetY());
		mapsChangeUpdate();

	}
	void ScreenMap::mapsChangeUpdate()
	{
		if(currentMap->CheckWidthOutOfWindowsLeft())
		{
			mapPast++;
			mapNow++;
			mapNext++;
			recorderUpdater();
			pastMap = maps[mapPast];
			currentMap = maps[mapNow];
			nextMap = maps[mapNext];
			changeMapInitialize();
		}
		if(pastMap->CheckWidthOnLeftBorder())
		{
			mapNow--;
			mapNext--;
			mapPast--;
			recorderUpdater();
			/*if(mapRestriction(mapNow))//限制住mapNow 不給指向下一張地圖(因為沒地圖了)
				return;*/
			currentMap = maps[mapNow];
			nextMap = maps[mapNext];
			pastMap = maps[mapPast];
			changeMapInitialize();
		}
	}
	void ScreenMap::Reset()
	{
		mapPast = 0;
		mapNow = 1;
		mapNext = 2;
		upMove = downMove = rightMove = leftMove = false;
		pastMap = maps[mapPast];
		currentMap = maps[mapNow];
		nextMap = maps[mapNext];
		changeMapInitialize();
	}
	void ScreenMap::changeMapInitialize()
	{
		int offset_past =0- pastMap->GetHeight() + SIZE_Y + offset_Heigth;
		int offset_now =0- currentMap->GetHeight() + SIZE_Y + offset_Heigth;
		int offset_next =0- nextMap->GetHeight() + SIZE_Y + offset_Heigth;

		pastMap -> SetMapLocation(0-pastMap->GetWidth(),offset_past);
		currentMap->SetMapLocation(0,offset_now);
		nextMap->SetMapLocation(currentMap->GetWidth(),offset_next);
	}
	void ScreenMap::recorderUpdater()
	{
		if(mapNow < 0)
			mapNow = maps.size() -1;
		if(mapNext < 0)
			mapNext  = maps.size() - 1;
		if(mapPast < 0)
			mapPast  = maps.size() - 1;
		if(mapNow > (int)maps.size() -1)
			mapNow = 0;
		if(mapNext > (int)maps.size() -1)
			mapNext = 0;
		if(mapPast > (int)maps.size() -1)
			mapPast = 0;
	}//地圖輪迴
/*	bool ScreenMap::mapRestriction(int& borderMap)
	{
		int maxMap = maps.size();
		if(borderMap > maxMap-1)
		{
			borderMap --;
			return true;
		}
		if(borderMap < 1)
		{
			borderMap ++;
			return true;
		}
		return false;

	}*/
	void ScreenMap::OnShow()
	{
		currentMap->OnShow();
		nextMap->OnShow();
		pastMap ->OnShow();
	}
	void ScreenMap::SetKeyDownControl(UINT keyin)
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
	}
	void ScreenMap::SetKeyUpControl(UINT keyin)
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
	}
	void ScreenMap::RepeatMode(bool repeat){}

	int ScreenMap::Different_Map_HeigthOffset(int choose)
	{
		return SIZE_Y - maps[choose]->GetHeight();
	}
