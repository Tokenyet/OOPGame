#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H
#include "Obstacle.h"
#include "Human.h"
#include "Scroll_System.h"
#include "Collision_System.h"
#include "FileManager.h"

class LevelEditor
{
private:
	FileManager* fileManager;
	string *fileStatementTemp;
	vector<string> object_string_Data;
	vector<vector<int>> object_int_data;
	vector<int>  fileAnaylizer(string source_String);
	vector<int>  position_Anaylizer(string position);

	Human *charcter;
	Scroll_System * scroll_system; //Test
	Collision_System * collision_system; //Test
	vector<Obstacle*> obstacles;

	
	void saveData();
	void addObstacles(CPoint); 
	void SystemSync();
public:
	LevelEditor();
	vector<Obstacle*> ObjectsData();
	void TestShowObjects();
	void Initialization(Scroll_System*,Collision_System*,Human*);
	void SetCharcterPosition(Human *charcter);
	void KeyDownChange(UINT);
	void MouseOnClick(bool,CPoint);
	void MouseUpClick(bool);
};

string int2str(int i);
#endif