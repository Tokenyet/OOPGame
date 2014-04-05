#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H
#include "Obstacle.h"
#include "Human.h"
#include "Scroll_System.h"
#include "Collision_System.h"
#include "FileManager.h"

enum ObjectData
{
	ColBlock = 0,//"Bitmaps/block-5.bmp"
	RowBlock = 1,//"Bitmaps/block-4.bmp"
	MushRoom = 3,//"Bitmaps/l_mushroom.bmp"
};

class LevelEditor
{
private:
	FileManager* fileManager;
	string *fileStatementTemp;
	vector<string> object_string_Data;
	vector<ObjectData> object_type_data;
	void fileAnaylizer(string source_String);

	vector<int>  position_Anaylizer(string position);

	Human *charcter;
	Scroll_System * scroll_system; //Test
	Collision_System * collision_system; //Test

	vector<Obstacle*> obstacles;//container
	vector<Enemy*> enemys;
	void Obstacle_BitmapLoader(Obstacle*,ObjectData);
	void Enemy_BitmapLoader(Enemy*,ObjectData);
	void addObstacles(CPoint); 
	void addEnemys(CPoint);
	bool DelObstacle(int recorder_index,int object_index,int x,int y,int offset);
	bool DelEnemy(int recorder_index ,int object_index,int x,int y,int offset);
	void saveData();
	ObjectData classType;//KeyBoardSelect
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
	vector<Obstacle*>* GetObstaclsDatas();
	vector<Enemy*>* GetEnemysDatas();
};

string int2str(int i);
#endif