#ifndef SCREENMAP_H
#define SCREENMAP_H
#include "StdAfx.h"
#include <vector>
#include "Map.h"

class ScreenMap
{
private:
	int real_X,real_Y;
	int offset_Heigth;//���������ܤ�
	int maps_Wt,maps_Ht;
	int windows_Wt,windows_Ht;
	bool repeatMode;
	vector<Map*> maps;
	Map *currentMap,*nextMap,*pastMap;
	int mapNow,mapNext,mapPast;
	bool upMove,downMove,rightMove,leftMove;
	void mapsChangeUpdate();
	//bool mapRestriction(int& borderMap);//�a�ϵL���j �|���갵
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
	int Different_Map_HeigthOffset(int);
};
#endif