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
	//delete charcter;
	//delete scroll_system; //Test
	//delete collision_system; //Test

	for(size_t i = 0;i<obstacles.size();i++)
	delete obstacles[i];//container
	for(size_t i = 0;i<enemys.size();i++)
	delete enemys[i];
	for(size_t i = 0;i<things.size();i++)
	delete things[i];
	obstacles.clear();
	enemys.clear();
	things.clear();
}

void LevelEditor::Reset()
{
	delete fileManager;
	fileManager = new FileManager("level-test.dat");
	fileStatementTemp = fileManager->GetData();
	object_string_Data.clear();
	object_type_data.clear();

	for(size_t i = 0;i<obstacles.size();i++)
	delete obstacles[i];//container
	for(size_t i = 0;i<enemys.size();i++)
	delete enemys[i];
	for(size_t i = 0;i<things.size();i++)
	delete things[i];
	obstacles.clear();
	enemys.clear();
	things.clear();


	for(int i = 0;i < fileManager->GetLine();i++)
		fileAnaylizer(fileStatementTemp[i]);
	Initialization(this->scroll_system,this->collision_system,this->charcter);
}

void LevelEditor::NextStage()
{
	delete fileManager;
	fileManager = new FileManager("level-2.dat");
	fileStatementTemp = fileManager->GetData();
	object_string_Data.clear();
	object_type_data.clear();

	for(size_t i = 0;i<obstacles.size();i++)
	delete obstacles[i];//container
	for(size_t i = 0;i<enemys.size();i++)
	delete enemys[i];
	for(size_t i = 0;i<things.size();i++)
	delete things[i];
	obstacles.clear();
	enemys.clear();
	things.clear();


	for(int i = 0;i < fileManager->GetLine();i++)
		fileAnaylizer(fileStatementTemp[i]);
	this->scroll_system->ChangeMap("Bitmaps/stage2.bmp");
	Initialization(this->scroll_system,this->collision_system,this->charcter);
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

	if(class_type < 3)
	{
		Obstacle *TempObstacle = new Obstacle(position_x_y[0],position_x_y[1]);
		obstacles.push_back(TempObstacle);
	}
	else if(class_type == 3)
	{
		int EnemyAI = rand()%2;
		int EnemyType = rand()%9+10;
		CharcterType enemyType = (CharcterType)EnemyType;
		Enemy *TempEnemy;
		if(EnemyAI == 0)
		TempEnemy = new Enemy(position_x_y[0],position_x_y[1],enemyType);
		else
		TempEnemy = new Enemy_OverWall(position_x_y[0],position_x_y[1],enemyType);
		enemys.push_back(TempEnemy);
	}
	else if(class_type == ArmorThing)
	{
		Arrow_Equip *TempThing = new Arrow_Equip(position_x_y[0],position_x_y[1]);
		things.push_back(TempThing);
	}
	else if(class_type == MageThing)
	{
		Mage_Equip *TempThing = new Mage_Equip(position_x_y[0],position_x_y[1]);
		things.push_back(TempThing);
	}
	//TempObstacle->LoadBitmapA("Bitmaps/block-5.bmp");
	object_type_data.push_back((ObjectData)class_type);

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
	int ob_index = 0;
	int enemy_index = 0;
	int thing_index = 0;
	for(size_t i = 0; i< object_type_data.size();i++)
	{
		switch(object_type_data[i])
		{
		case 0:
		case 1:
			Obstacle_BitmapLoader(obstacles[ob_index],object_type_data[i]);
			ob_index ++;
			break;
		case 3:
			Enemy_BitmapLoader(enemys[enemy_index],object_type_data[i]);
			enemy_index++;
			break;
		case 5:
			Thing_BitmapLoader(things[thing_index],object_type_data[i]);
			thing_index++;
			break;
		case 6:
			Thing_BitmapLoader(things[thing_index],object_type_data[i]);
			thing_index++;
			break;
		}
	}
}
void LevelEditor::Obstacle_BitmapLoader(Obstacle* obstacle,ObjectData obData)
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
void LevelEditor::Enemy_BitmapLoader(Enemy* enemy,ObjectData obData)
{
	switch(obData)
	{
		case 3:
		enemy->LoadBitmapA();
		break;
		default:
			ASSERT(1);
	}
}
void LevelEditor::Thing_BitmapLoader(Thing* thing,ObjectData obData)
{
	switch(obData)
	{
		case ArmorThing:
		thing->LoadBitmapA("Bitmaps/L/l_arror-1.bmp",RGB(0,0,0));
		break;
		case MageThing:
		thing->LoadBitmapA("Bitmaps/L/l_magicball.bmp",RGB(0,0,0));
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
	object_type_data.push_back((ObjectData)classType);
	obstacles.push_back(newObstacle);
	SystemSync();
}
void LevelEditor::addEnemys(CPoint position)
{
	int offset = charcter->GetX() - SIZE_X/2 +50; 
	Enemy* newEnemy = new Enemy(position.x + offset,position.y,Type_MushRoom);

	string newObstaclePosition = "";
	newObstaclePosition += int2str(classType);
	newObstaclePosition += "@(";
	newObstaclePosition += int2str(position.x + offset);
	newObstaclePosition += ",";
	newObstaclePosition += int2str(position.y);
	newObstaclePosition += ")";
	object_string_Data.push_back(newObstaclePosition);
	newEnemy->GetX() -= offset;//顯示時需抵補回來

	Enemy_BitmapLoader(newEnemy,classType);
	object_type_data.push_back((ObjectData)classType);
	enemys.push_back(newEnemy);
	SystemSync();
}
void LevelEditor::addThings(CPoint position)
{
	int offset = charcter->GetX() - SIZE_X/2 +50; 
	Thing * newThing;
	if(classType == ArmorThing)
		newThing = new Arrow_Equip(position.x + offset,position.y);
	else
		newThing = new Mage_Equip(position.x + offset,position.y);
	//newThing->LoadBitmapA("",RGB(0,0,0));
	string newObstaclePosition = "";
	newObstaclePosition += int2str(classType);
	newObstaclePosition += "@(";
	newObstaclePosition += int2str(position.x + offset);
	newObstaclePosition += ",";
	newObstaclePosition += int2str(position.y);
	newObstaclePosition += ")";
	object_string_Data.push_back(newObstaclePosition);
	newThing->GetX() -= offset;//顯示時需抵補回來

	Thing_BitmapLoader(newThing,classType);
	object_type_data.push_back((ObjectData)classType);
	things.push_back(newThing);
	SystemSync();

}


void LevelEditor::SystemSync()
{
	if(classType < 3)
	{
		scroll_system->AddObject(obstacles[obstacles.size()-1]);
		collision_system->Add_ObstacleCollisions(obstacles[obstacles.size()-1]);
	}
	else if(classType == ArmorThing||classType == MageThing)
	{
		scroll_system->AddObject(things[things.size()-1]);
	}
	else
	{
		//scroll_system->AddEnemy(enemys[enemys.size()-1]);
		//collision_system->Add_EnemyCollisions(enemys[enemys.size()-1]);
	}
	scroll_system->OnMove();
	collision_system->OnCheck();
}

vector<Obstacle*>* LevelEditor::GetObstaclsDatas()
{
	return &obstacles;
}
vector<Enemy*>* LevelEditor::GetEnemysDatas()
{return &enemys;}

vector<Thing*>* LevelEditor::GetThingsDatas()
{return &things;}

void LevelEditor::SetCharcterPosition(Human *charcter){}
void LevelEditor::KeyDownChange(UINT keyin)
{
	const char KEY_Z  = 90; // z col
	const char KEY_X  = 88; // x row
	const char KEY_C  = 67; // c mushroom
	const char KEY_V  = 86; // v Armorthing
	const char KEY_B = 66;  // b mageThing
	const char KEY_N = 78;
	const char KEY_M = 77;
	const char KEY_SPACE = 0x20;// save
	if(keyin == KEY_SPACE)
	saveData();
	if(keyin == KEY_Z)
		classType = ColBlock;
	if(keyin == KEY_X)
		classType = RowBlock;
	if(keyin == KEY_C)
		classType = MushRoom;
	if(keyin == KEY_V)
		classType = ArmorThing;
	if(keyin == KEY_B)
		classType = MageThing;
}
void LevelEditor::LMouseOnClick(bool on,CPoint position)
{	

	int offset = (charcter->GetX() - SIZE_X/2 +50); 
	if(offset > 0)
		offset%=32;
	else
		offset = (0-offset)%32;
	/*int charcter_offset;
	charcter_offset = %32;*/
	int origin_x = position.x;
	int origin_y = position.y;
	int offset_x = position.x%32 + offset;//-charcter_offset;
	int offset_y = position.y%32;
	CPoint newPosition(origin_x-offset_x,origin_y-offset_y);
	if(classType < 3)
	addObstacles(newPosition);
	else if(classType == MushRoom)
	addEnemys(newPosition);
	else if(classType == ArmorThing||classType == MageThing)
	addThings(newPosition);
}
void LevelEditor::LMouseUpClick(bool off){}
void LevelEditor::RMouseOnClick(bool on,CPoint position)
{
	/*
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

		*/
	int offset = charcter->GetDistanceFromOriginX();
	int x =  position.x ;
	int y =  position.y ;
	int obstacle_index = 0;
	int enemy_index = 0;
	int thing_index = 0;
	for(size_t i = 0;i<object_type_data.size();i++)
	{
		switch(object_type_data[i])
		{
			case ColBlock:
			case RowBlock:
				if(obstacles.empty())
					break;
				if(obstacles[obstacle_index])
					if(DelObstacle(i,obstacle_index,x,y,offset))
						return;
				obstacle_index++;
				break;
			case MushRoom:
				if(enemys.empty())
					break;
				if(enemys[enemy_index])
					if(DelEnemy(i,enemy_index,x,y,offset))
						return;
					enemy_index++;
				break;
			case ArmorThing:
			case MageThing:
				if(things.empty())
					break;
				if(things[thing_index])
					if(DelThing(i,thing_index,x,y,offset))
						return;
					thing_index++;
				break;
			default:
				ASSERT(0);
				break;
		}
	}
}



bool LevelEditor::DelObstacle(int recorder_index,int object_index,int x,int y,int offset)
{
	 x += offset;
	if(x < obstacles[object_index]->GetOriginX() + obstacles[object_index]->GetRect().Get_Width()&&
		y < obstacles[object_index]->GetRect().Get_Ry()&&
		x > obstacles[object_index]->GetOriginX()&&
		y > obstacles[object_index]->GetRect().Get_Ly())
			{
			   collision_system->Del_ObstacleCollisions(obstacles[object_index]);
			   scroll_system->DelObject(obstacles[object_index]);
			   delete obstacles[object_index];
			   obstacles.erase(obstacles.begin()+object_index); 
			   object_type_data.erase(object_type_data.begin()+recorder_index);
			   object_string_Data.erase(object_string_Data.begin()+recorder_index);
			   return true;
			}
	return false;

}

bool LevelEditor::DelEnemy(int recorder_index ,int object_index,int x,int y,int offset)
{
	int width = enemys[object_index]->GetRect().GetWidth()+5;
	int heigth = enemys[object_index]->GetRect().GetHeight()+5;
	if(x <= enemys[object_index]->GetX() + width&&
		y <= enemys[object_index]->GetY() + heigth&&
		x >= enemys[object_index]->GetX()&&
		y >= enemys[object_index]->GetY())
	{
			   //collision_system->Del_EnemyCollisions(enemys[object_index]);
			   //scroll_system->DelEnemy(enemys[object_index]);
			   delete enemys[object_index];
			   enemys.erase(enemys.begin()+object_index);
			   object_type_data.erase(object_type_data.begin()+recorder_index);
			   object_string_Data.erase(object_string_Data.begin()+recorder_index);
			   return true;
	}
	return false;
}


bool LevelEditor::DelThing(int recorder_index ,int object_index,int x,int y,int offset)
{
	int width = things[object_index]->GetRect().Get_Width()+5;
	int heigth = things[object_index]->GetRect().Get_Heigth()+5;
	if(x <= things[object_index]->GetX() + width&&
		y <= things[object_index]->GetY() + heigth&&
		x >= things[object_index]->GetX()&&
		y >= things[object_index]->GetY())
	{
			   //collision_system->Del_EnemyCollisions(enemys[object_index]);
			   //scroll_system->DelEnemy(enemys[object_index]);
			   scroll_system->DelObject(things[object_index]);
			   delete things[object_index];
			   things.erase(things.begin()+object_index);
			   object_type_data.erase(object_type_data.begin()+recorder_index);
			   object_string_Data.erase(object_string_Data.begin()+recorder_index);
			   return true;
	}
	return false;
}


void LevelEditor::TestShowObjects()
{
	for(size_t i = 0;i<obstacles.size();i++)
		obstacles[i]->OnShow();
	/*for(size_t i = 0;i<enemys.size();i++)
		enemys[i]->OnShow();*/
}


string int2str(int i) {
string s;
stringstream ss(s);
ss << i;
return ss.str();
}