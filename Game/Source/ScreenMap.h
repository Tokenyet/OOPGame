#ifndef SCREENMAP_H
#define SCREENMAP_H
#include "StdAfx.h"
#include <vector>
#include "Map.h"

class ScreenMap
{
private:
	int real_X,real_Y;
	int offset_Heigth;
	int maps_Wt,maps_Ht;
	int windows_Wt,windows_Ht;
	bool repeatMode;
	vector<Map*> maps;
	Map *currentMap,*nextMap,*pastMap;
	int mapNow,mapNext,mapPast;
	bool upMove,downMove,rightMove,leftMove;
	void mapsChangeUpdate();
	//bool mapRestriction(int& borderMap);//地圖無輪迴 尚未實做
	void changeMapInitialize();
	void recorderUpdater();
public:
	ScreenMap();
	~ScreenMap();
	void Initialization(vector<Map> &maps);
	void Reset();
	void SetKeyDownControl(UINT keyin);
	void SetKeyUpControl(UINT keyin);
	void AddMap(vector<Map> &maps);
	void AddMap(Map* map);
	void RepeatMode(bool repeat);
	void OnMove();
	void OnShow();
};
#endif