#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include "StdAfx.h"
#include "Human.h"
#include "ICollision.h"
#include <vector>
using namespace std;

class Collision_System
{
private:
	vector<Human*> heroBoxes;
	vector<ICollision*> enemyBoxes;
	vector<ICollision*> obstacleBoxes;
	vector<ICollision*> bulletBoxes;
	void checkHuman_Obstacle();
	void checkHuman_ObstacleWhereCollision(Human* humanBoxes,ICollision* obstacleBoxes);
	void resetHuman_Collision(ICollision* resetBoxes);
public:
	Collision_System();
	~Collision_System();
	void OnCheck ();
	void Load_HeroCollisions (vector<Human*>);
	void Load_EnemyCollisions (vector<ICollision*>);
	void Load_ObstacleCollisions (vector<ICollision*>);
	void Load_bulletCollisions (vector<ICollision*>);

};

#endif