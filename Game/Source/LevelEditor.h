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
	vector<vector<string>> real_Data;
	vector<string> fileAnaylizer(string source_String);


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
	void Initialization(Scroll_System*,Collision_System*,Human*);
	void SetCharcterPosition(Human *charcter);
	void KeyDownChange(UINT);
	void MouseOnClick(bool,CPoint);
	void MouseUpClick(bool);
};

string int2str(int i);
#endif