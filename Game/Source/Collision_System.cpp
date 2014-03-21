#include "StdAfx.h"
#include "Human.h"
#include "ICollision.h"
#include "CRectangle.h"
#include "Collision_System.h"
#include <vector>
//using namespace std;


	Collision_System::Collision_System(){}
	Collision_System::~Collision_System(){}
	void Collision_System::OnCheck()
	{
		checkHuman_Obstacle();
	}
	void Collision_System::Load_HeroCollisions (vector<Human*> heroBoxes)
	{this->heroBoxes = heroBoxes;}
	void Collision_System::Load_EnemyCollisions (vector<ICollision*> enemyBoxes)
	{this->enemyBoxes = enemyBoxes;}
	void Collision_System::Load_ObstacleCollisions (vector<ICollision*> obstacleBoxes)
	{this->obstacleBoxes = obstacleBoxes;}
	void Collision_System::Load_bulletCollisions (vector<ICollision*> bulletBoxes)
	{this->bulletBoxes = bulletBoxes;}

	//檢查與設定物體人物(Human)碰撞位置
	void Collision_System::checkHuman_Obstacle()
	{
		for(size_t i=0;i<heroBoxes.size();i++)
			for(size_t j = 0;j<obstacleBoxes.size();j++)
			{
				checkHuman_ObstacleWhereCollision(heroBoxes[i],obstacleBoxes[i]);
				/*if(heroBoxes[i]->GetRect().Intersect(obstacleBoxes[i]->GetRect()))
				{            
					checkHuman_ObstacleWhereCollision(heroBoxes[i],obstacleBoxes[i]);
				}*/
			/*	else
				{
					resetHuman_Collision(heroBoxes[i]);
				}*/
			}
	}

	void Collision_System::checkHuman_ObstacleWhereCollision(Human* humanBox,ICollision* obstacleBox)
	{
		bool human_Up = humanBox->GetRect().UpIntersect(obstacleBox->GetRect());
		bool human_Down = humanBox->GetRect().DownIntersect(obstacleBox->GetRect());
		bool human_Right = humanBox->GetRect().RightIntersect(obstacleBox->GetRect());
		bool human_Left = humanBox->GetRect().LeftIntersect(obstacleBox->GetRect());
		if(human_Up)
			humanBox->GetY() = obstacleBox->GetRect().Get_Ly() + obstacleBox->GetRect().Get_Heigth();
		if(human_Down)
			humanBox->GetY() = obstacleBox->GetRect().Get_Ly() - humanBox->GetRect().GetHeight();
		if(human_Right)
			humanBox->GetX() = obstacleBox->GetRect().Get_Lx() + obstacleBox->GetRect().Get_Width();
		if(human_Left)
			humanBox->GetX() = obstacleBox->GetRect().Get_Lx() - humanBox->GetRect().GetHeight();
		
		/*
		bool below_restriction = 
			(obstacleBox->GetRect().Get_Ly() - humanBox->GetRect().Get_Ry() < 4) && (obstacleBox->GetRect().Get_Ly() - humanBox->GetRect().Get_Ly()  >= humanBox->GetRect().Get_Heigth() -10);
		bool above_restriction =
			(humanBox->GetRect().Get_Ly() -obstacleBox->GetRect().Get_Ry()  < 4) && (humanBox->GetRect().Get_Ly() - obstacleBox->GetRect().Get_Ly()  >= obstacleBox->GetRect().Get_Heigth() -10);
			if (humanBox->GetRect().Get_Ly() > obstacleBox->GetRect().Get_Ly() &&above_restriction ) //we have collided with an object above us. 
            {
				//humanBox->GetIntersect(0) = true;
				humanBox->GetY() = obstacleBox->GetRect().Get_Ly() + obstacleBox->GetRect().Get_Heigth();
            }
            if(humanBox->GetRect().Get_Ry() < obstacleBox->GetRect().Get_Ry()&&below_restriction)//we have collided with an object below us.
            {
				//humanBox->GetIntersect(1) = true;
				humanBox->GetY() = obstacleBox->GetRect().Get_Ly() - humanBox->GetRect().Get_Heigth();
            }
            if(humanBox->GetRect().Get_Lx() > obstacleBox->GetRect().Get_Lx()) //We have collided with an object to the right.
            {
				humanBox->GetX() = obstacleBox->GetRect().Get_Lx() + obstacleBox->GetRect().Get_Width();
				//humanBox->GetIntersect(2) = true;
            }
		    if(humanBox->GetRect().Get_Rx() < obstacleBox->GetRect().Get_Rx())// We have collided with an object to the left;
            {
				//humanBox->GetIntersect(3) = true;
				humanBox->GetX() = obstacleBox->GetRect().Get_Lx() - humanBox->GetRect().Get_Width();
            }*/
	}
	/*
	void Collision_System::resetHuman_Collision(ICollision* resetBoxes)
	{
		const int KindOfCollision = 6;
		for(int i = 0;i< KindOfCollision;i++)
			resetBoxes->GetIntersect(i) = false;
	}*/