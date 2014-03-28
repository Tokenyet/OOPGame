#include "StdAfx.h"
#include "LevelEditor.h"
#include "FileManager.h"
#include "Obstacle.h"
#include "Scroll_System.h"
#include "Collision_System.h"
#include <sstream>

#include "ICollision.h"

LevelEditor::LevelEditor()
{
	fileManager = new FileManager("level-test.dat");
	fileStatementTemp = fileManager->GetData();
	for(int i = 0;i < fileManager->GetLine();i++)
		object_int_data[i] = fileAnaylizer(fileStatementTemp[i]);
}
vector<int> LevelEditor::fileAnaylizer(string source_String)
{
	vector<int> data;
	int split[3];
	split[0] = source_String.find("@",0);
	split[1] = source_String.find("(",split[0]+1);
	split[2] = source_String.find(",",split[1]+1);
	data.push_back(atoi(source_String.substr(0,split[0]).c_str()));
	data.push_back(atoi(source_String.substr(split[0]+1,split[1] - split[0] -1).c_str()));
	data.push_back(atoi(source_String.substr(split[1]+1).c_str()));
	return data;
}
vector<int> LevelEditor::position_Anaylizer(string position)
{

}



void LevelEditor::Initialization(Scroll_System* scroll,Collision_System* collisionS,Human* charcter)
{
	this->charcter = charcter;
	this->scroll_system = scroll;
	this->collision_system = collisionS;
/*	for(size_t i= 0;i<obstacles.size();i++)
	obstacles[i] = new Obstacle(object_int_data[i][1],object_int_data[i][2]);*/
}
void LevelEditor::saveData()
{
	fileManager->SetLineData(object_string_Data);
}
void LevelEditor::addObstacles(CPoint position)
{
	int offset = charcter->GetX() - SIZE_X/2 +50; 
	Obstacle* newObstacle = new Obstacle(position.x + offset,position.y);

	string newObstaclePosition = "";
	newObstaclePosition += "0";
	newObstaclePosition += "@(";
	newObstaclePosition += int2str(newObstacle->GetOriginX());
	newObstaclePosition += ",";
	newObstaclePosition += int2str(newObstacle->GetOriginY());
	newObstaclePosition += ")";
	object_string_Data.push_back(newObstaclePosition);

	obstacles.push_back(newObstacle);
	SystemSync();
}
void LevelEditor::SystemSync()
{
	scroll_system->AddObject(obstacles[obstacles.size()-1]);
	scroll_system->OnMove();
	collision_system->Add_ObstacleCollisions(obstacles[obstacles.size()-1]);
	collision_system->OnCheck();
}
vector<Obstacle*> LevelEditor::ObjectsData()
{
	return obstacles;
}
void LevelEditor::SetCharcterPosition(Human *charcter){}
void LevelEditor::KeyDownChange(UINT Keyin)
{
	const char KEY_Z  = 90; // z
	const char KEY_X  = 88; // x
	const char KEY_C  = 67; // c
	const char KEY_V  = 86; // v
	const char KEY_SPACE = 0x20;
	saveData();
}
void LevelEditor::MouseOnClick(bool on,CPoint position)
{
	addObstacles(position);
}
void LevelEditor::MouseUpClick(bool off){}


void LevelEditor::TestShowObjects()
{
	for(size_t i = 0;i<obstacles.size();i++)
		obstacles[i]->OnShow();
}


string int2str(int i) {
string s;
stringstream ss(s);
ss << i;
return ss.str();
}