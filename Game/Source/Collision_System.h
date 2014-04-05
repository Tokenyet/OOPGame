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
	vector<Enemy*> *enemyBoxes;
	vector<ICollision*> *obstacleBoxes;
	vector<ICollision*> bulletBoxes;
	void checkHuman_Obstacle();
	void checkEnemy_Obstacle();
	void checkHuman_ObstacleWhereCollision(Human* humanBoxes,ICollision* obstacleBoxes);
	void resetHuman_Collision(ICollision* resetBoxes);
public:
	Collision_System();
	~Collision_System();
	void OnCheck ();
	void Load_HeroCollisions (vector<Human*>);
	void Load_EnemyCollisions (vector<Enemy*>*);
	void Add_EnemyCollisions(Enemy* enemy);
	void Del_EnemyCollisions(Enemy* enemy);
	void Load_ObstacleCollisions (vector<ICollision*>*);
	void Add_ObstacleCollisions(ICollision*);
	void Del_ObstacleCollisions(ICollision*);
	void Load_bulletCollisions (vector<ICollision*>);

};

#endif