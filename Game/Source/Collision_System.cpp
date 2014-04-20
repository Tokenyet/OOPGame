#include "StdAfx.h"
#include "Enemy.h"
#include "Human.h"
#include "Charcter.h"
#include "ICollision.h"
#include "CRectangle.h"
#include "Collision_System.h"
#include <vector>

//using namespace std;


	Collision_System::Collision_System(){}
	Collision_System::~Collision_System()
	{
		for(size_t i = 0;i< heroBoxes.size();i++)
			delete heroBoxes[i];
	/*	for(size_t i = 0;i< enemyBoxes->size();i++)
			delete (*enemyBoxes)[i];*/
		/*for(size_t i = 0;i< obstacleBoxes->size();i++)
			delete (*obstacleBoxes)[i];*/
		for(size_t i = 0;i< bulletBoxes.size();i++)
			delete bulletBoxes[i];
	}
	void Collision_System::OnCheck()
	{
		checkHuman_Obstacle();
		checkEnemy_Obstacle();
		checkHuman_AttackEnemy();
	}
	void Collision_System::Load_HeroCollisions (vector<Human*> heroBoxes)
	{this->heroBoxes = heroBoxes;}
	void Collision_System::Load_EnemyCollisions (vector<Enemy*>* enemyBoxes)
	{this->enemyBoxes = enemyBoxes;}
	void Collision_System::Add_EnemyCollisions(Enemy* enemy)
	{this->enemyBoxes->push_back(enemy);}
	void Collision_System::Del_EnemyCollisions(Enemy* enemy)
	{
		for(size_t i=0;i<enemyBoxes->size();i++)
			if((*enemyBoxes)[i]==enemy)
				enemyBoxes->erase(enemyBoxes->begin()+i);
	}

	void Collision_System::Load_ObstacleCollisions (vector<ICollision*>* obstacleBoxes)
	{this->obstacleBoxes = obstacleBoxes;}
	void Collision_System::Add_ObstacleCollisions(ICollision* obstacle)
	{this->obstacleBoxes->push_back(obstacle);}
	void Collision_System::Del_ObstacleCollisions(ICollision* obstacle)
	{
		for(size_t i=0;i<obstacleBoxes->size();i++)
			if((*obstacleBoxes)[i]==obstacle)
				(*obstacleBoxes).erase((*obstacleBoxes).begin()+i);
	}
	void Collision_System::Load_bulletCollisions (vector<ICollision*> bulletBoxes)
	{this->bulletBoxes = bulletBoxes;}

	//檢查與設定物體人物(Human)碰撞位置
	void Collision_System::checkHuman_Obstacle()
	{
		for(size_t i=0;i<heroBoxes.size();i++)
			for(size_t j = 0;j<obstacleBoxes->size();j++)
			{
				checkHuman_ObstacleWhereCollision(heroBoxes[i],(*obstacleBoxes)[j]);
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
	void Collision_System::checkEnemy_Obstacle()
	{
		for(size_t i=0;i<enemyBoxes->size();i++)
			for(size_t j = 0;j<obstacleBoxes->size();j++)
			{
				checkHuman_ObstacleWhereCollision((*enemyBoxes)[i],(*obstacleBoxes)[j]);
			}
	}
	void Collision_System::checkHuman_ObstacleWhereCollision(Human* humanBox,ICollision* obstacleBox)
	{
		bool human_Up = humanBox->GetRect().UpIntersect(obstacleBox->GetRect());
		bool human_Down = humanBox->GetRect().DownIntersect(obstacleBox->GetRect());
		bool human_Right = humanBox->GetRect().RightIntersect(obstacleBox->GetRect());
		bool human_Left = humanBox->GetRect().LeftIntersect(obstacleBox->GetRect());
		if(human_Up)
			humanBox->setUpRestriction(obstacleBox->GetRect().Get_Ry()+2)
			 = true;
			//humanBox->GetY() = obstacleBox->GetRect().Get_Ly() + obstacleBox->GetRect().Get_Heigth()+5;
		if(human_Down)
			humanBox->setDownRestriction(obstacleBox->GetRect().Get_Ly()-2)
			 = true;
			//humanBox->GetY() = obstacleBox->GetRect().Get_Ly() - humanBox->GetRect().GetHeight()-20;
		if(human_Right)
			humanBox->setRightRestriction(obstacleBox->GetRect().Get_Lx()-1)
			 = true;
			//humanBox->GetX() = obstacleBox->GetRect().Get_Lx() - humanBox->GetRect().GetWidth()-20;
		if(human_Left)
			humanBox->setLeftRestriction(obstacleBox->GetRect().Get_Rx()+1)
			 = true;
			//humanBox->GetX() = obstacleBox->GetRect().Get_Lx() + obstacleBox->GetRect().Get_Width()+5;
		
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
	void Collision_System::checkHuman_AttackEnemy()
	{
		for(size_t i=0;i<heroBoxes.size();i++)
			for(size_t j = 0;j<enemyBoxes->size();j++)
			{
				if(checkHuman_EnemyCollision(heroBoxes[i],(*enemyBoxes)[j]))
					Del_EnemyCollisions((*enemyBoxes)[j]);
			}
	}
	bool Collision_System::checkHuman_EnemyCollision(Human* charcter,Human* enemy)
	{
		Charcter* Ccharcter = dynamic_cast<Charcter*>(charcter);
		CRectangle enemyBody = enemy->GetRect().GetOriginRect();
		if(Ccharcter != NULL)
		{
		bool intersect = charcter->GetRect().GetOriginRect().Intersect(enemyBody);
			if(Ccharcter->GetAttacking()&&intersect)
			{
				return true;
			}
		}
		return false;
	}
	/*
	void Collision_System::resetHuman_Collision(ICollision* resetBoxes)
	{
		const int KindOfCollision = 6;
		for(int i = 0;i< KindOfCollision;i++)
			resetBoxes->GetIntersect(i) = false;
	}*/