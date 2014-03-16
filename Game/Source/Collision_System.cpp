#include "StdAfx.h"
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
	void Collision_System::Load_HeroCollisions (vector<ICollision*> heroBoxes)
	{this->heroBoxes = heroBoxes;}
	void Collision_System::Load_EnemyCollisions (vector<ICollision*> enemyBoxes)
	{this->enemyBoxes = enemyBoxes;}
	void Collision_System::Load_ObstacleCollisions (vector<ICollision*> obstacleBoxes)
	{this->obstacleBoxes = obstacleBoxes;}
	void Collision_System::Load_bulletCollisions (vector<ICollision*> bulletBoxes)
	{this->bulletBoxes = bulletBoxes;}

	void Collision_System::checkHuman_Obstacle()
	{
		for(size_t i=0;i<heroBoxes.size();i++)
			for(size_t j = 0;j<obstacleBoxes.size();j++)
			{
				heroBoxes[i]->GetIntersect(0)
					= heroBoxes[i]->GetRect().Intersect(obstacleBoxes[i]->GetRect());
			}

	}