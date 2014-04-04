#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H
#include "Obstacle.h"
#include "Human.h"
#include "Scroll_System.h"
#include "Collision_System.h"
#include "FileManager.h"

enum ObstacleData
{
	ColBlock = 0,//"Bitmaps/block-5.bmp"
	RowBlock = 1,//"Bitmaps/block-4.bmp"
};

class LevelEditor
{
private:
	FileManager* fileManager;
	string *fileStatementTemp;
	vector<string> object_string_Data;
	vector<ObstacleData> object_type_data;
	void fileAnaylizer(string source_String);
	void Obstacle_BitmapLoader(Obstacle*,ObstacleData);
	vector<int>  position_Anaylizer(string position);

	Human *charcter;
	Scroll_System * scroll_system; //Test
	Collision_System * collision_system; //Test

	vector<Obstacle*> obstacles;//container
	
	void saveData();
	ObstacleData classType;//KeyBoardSelect
	void addObstacles(CPoint); 
	void SystemSync();
public:
	LevelEditor();
	~LevelEditor();
	void TestShowObjects();
	void Initialization(Scroll_System*,Collision_System*,Human*);
	void SetCharcterPosition(Human *charcter);
	void KeyDownChange(UINT);
	void LMouseOnClick(bool,CPoint);
	void RMouseOnClick(bool,CPoint);
	void LMouseUpClick(bool);
	vector<Obstacle*> GetObstaclsDatas();
};

string int2str(int i);
#endif