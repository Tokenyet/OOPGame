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
		real_Data[i] = fileAnaylizer(fileStatementTemp[i]);
}
vector<string> LevelEditor::fileAnaylizer(string source_String)
{
	vector<string> data;
	int split[3];
	split[0] = source_String.find("@",0);
	split[1] = source_String.find(",",split[0]+1);
	data.push_back(source_String.substr(0,split[0]));
	data.push_back(source_String.substr(split[0]+1,split[1] - split[0] -1));
	data.push_back(source_String.substr(split[1]+1));
	return data;
}
void LevelEditor::Initialization(Scroll_System* scroll,Collision_System* collisionS,Human* charcter)
{
	this->charcter = charcter;
	this->scroll_system = scroll;
	this->collision_system = collisionS;
}
void LevelEditor::saveData()
{
	vector<string> AllData;
	fileManager->SetLineData(AllData);
}
void LevelEditor::addObstacles(CPoint position)
{
	int offset = charcter->GetX() - SIZE_X/2 +50; 
	Obstacle* newObstacle = new Obstacle(position.x + offset,position.y);

	vector<string> newObstaclePosition(3);
	newObstaclePosition[0] = "0";
	newObstaclePosition[1] =int2str(position.x + offset);
	newObstaclePosition[2] =int2str(position.y);
	real_Data.push_back(newObstaclePosition);

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
vector<Obstacle*> LevelEditor::ObjectsData(){return obstacles;}
void LevelEditor::SetCharcterPosition(Human *charcter){}
void LevelEditor::KeyDownChange(UINT Keyin)
{
	const char KEY_Z  = 90; // z
	const char KEY_X  = 88; // x
	const char KEY_C  = 67; // c
	const char KEY_V  = 86; // v
	const char KEY_SPACE = 0x20;

}
void LevelEditor::MouseOnClick(bool on,CPoint position)
{
	addObstacles(position);
}
void LevelEditor::MouseUpClick(bool off){}


string int2str(int i) {
string s;
stringstream ss(s);
ss << i;
return ss.str();
}