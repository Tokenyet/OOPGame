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
		fileAnaylizer(fileStatementTemp[i]);
}

LevelEditor::~LevelEditor()
{
	delete fileManager;
}


void LevelEditor::fileAnaylizer(string source_String)
{
	object_string_Data.push_back(source_String);
	//�̷����O����Bitamp (�ʵe�OAnimation)
	//
	//���O@��m@Bitamp��m
	int split[4];
	int class_type;
	string position_string;
	split[0] = source_String.find("@");
	split[1] = source_String.find("(");
	split[2] = source_String.find(")");
	class_type = atoi(source_String.substr(0,split[0]).c_str());
	position_string = source_String.substr(split[1],split[2]-split[1]+1);
	vector<int> position_x_y = position_Anaylizer(position_string);

	Obstacle *TempObstacle = new Obstacle(position_x_y[0],position_x_y[1]);
	//TempObstacle->LoadBitmapA("Bitmaps/block-5.bmp");
	obstacles.push_back(TempObstacle);

}

vector<int> LevelEditor::position_Anaylizer(string position)//(1234,5678)
{
	vector<int> position_int;
	int split[3];
	split[0] = position.find("(");
	split[1] = position.find(",");
	split[2] = position.find(")");
	int x = atoi(position.substr(split[0]+1,split[1]-split[0]+1).c_str());
	int y = atoi(position.substr(split[1]+1,split[2]-split[1]+1).c_str());
	position_int.push_back(x);
	position_int.push_back(y);

	return position_int;
}



void LevelEditor::Initialization(Scroll_System* scroll,Collision_System* collisionS,Human* charcter)
{
	this->charcter = charcter;
	this->scroll_system = scroll;
	this->collision_system = collisionS;
	for(size_t i= 0;i<obstacles.size();i++)
		obstacles[i]->LoadBitmapA("Bitmaps/block-5.bmp");
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
void LevelEditor::KeyDownChange(UINT keyin)
{
	const char KEY_Z  = 90; // z
	const char KEY_X  = 88; // x
	const char KEY_C  = 67; // c
	const char KEY_V  = 86; // v
	const char KEY_SPACE = 0x20;
	if(keyin == KEY_SPACE)
	saveData();
}
void LevelEditor::LMouseOnClick(bool on,CPoint position)
{
	addObstacles(position);
}
void LevelEditor::LMouseUpClick(bool off){}


void LevelEditor::RMouseOnClick(bool on,CPoint position)
{
	int offset = charcter->GetDistanceFromOriginX();
	int x = position.x + offset;
	int y = position.y;
		for(size_t i = 0;i<obstacles.size();i++)
		{
			if(x < obstacles[i]->GetOriginX() + obstacles[i]->GetRect().Get_Width()&&
			   y < obstacles[i]->GetRect().Get_Ry()&&
			   x > obstacles[i]->GetOriginX()&&
			   y > obstacles[i]->GetRect().Get_Ly())
			{
			   collision_system->Del_ObstacleCollisions(obstacles[i]);
			   scroll_system->DelObject(obstacles[i]);
			   obstacles.erase(obstacles.begin()+i);
			   object_string_Data.erase(object_string_Data.begin()+i);
			}

		}

}


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