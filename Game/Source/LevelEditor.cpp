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
	classType = ColBlock;
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
	//依照類別給予Bitamp (動畫是Animation)
	//
	//類別@位置@Bitamp位置
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
	object_type_data.push_back((ObstacleData)class_type);

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
		Obstacle_BitmapLoader(obstacles[i],object_type_data[i]);
}

void LevelEditor::Obstacle_BitmapLoader(Obstacle* obstacle,ObstacleData obData)
{
	switch(obData)
	{
		case 0:
		obstacle->LoadBitmapA("Bitmaps/block-5.bmp");
		break;
		case 1:
		obstacle->LoadBitmapA("Bitmaps/block-4.bmp");
		break;
		default:
			ASSERT(1);
	}
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
	newObstaclePosition += int2str(classType);
	newObstaclePosition += "@(";
	newObstaclePosition += int2str(newObstacle->GetOriginX());
	newObstaclePosition += ",";
	newObstaclePosition += int2str(newObstacle->GetOriginY());
	newObstaclePosition += ")";
	object_string_Data.push_back(newObstaclePosition);

	Obstacle_BitmapLoader(newObstacle,classType);
	object_type_data.push_back((ObstacleData)classType);
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

vector<Obstacle*> LevelEditor::GetObstaclsDatas()
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
	if(keyin == KEY_Z)
		classType = ColBlock;
	if(keyin == KEY_X)
		classType = RowBlock;
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
			   object_type_data.erase(object_type_data.begin()+i);
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