#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include <vector>
#include "StdAfx.h"
#include "ICollision.h"
using namespace std;

class Collision_System
{
private:
	vector<ICollision*> heroBoxes;
	vector<ICollision*> enemyBoxes;
	vector<ICollision*> obstacleBoxes;
	vector<ICollision*> bulletBoxes;
	void checkHuman_Obstacle();
public:
	Collision_System();
	~Collision_System();
	void OnCheck ();
	void Load_HeroCollisions (vector<ICollision*>);
	void Load_EnemyCollisions (vector<ICollision*>);
	void Load_ObstacleCollisions (vector<ICollision*>);
	void Load_bulletCollisions (vector<ICollision*>);

};

#endif