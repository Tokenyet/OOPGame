#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H
#include "StdAfx.h"
#include "Human.h"
#include "ICollision.h"
#include "Thing.h"
#include "ArrowBox.h"
#include <vector>
using namespace std;

class Collision_System
{
private:
	vector<Human*> heroBoxes;
	vector<Enemy*> *enemyBoxes;
	vector<Thing*> *thingBoxes;
	vector<ICollision*> *obstacleBoxes;
	vector<ArrowBox*> *arrowBoxes;
	void checkHuman_Obstacle();
	void checkEnemy_Obstacle();
	void checkHuman_Thing();
	void checkHuman_AttackEnemy();
	void checkArrow_Obstacle();
	void checkArrow_Enemy();

	void checkHuman_ObstacleWhereCollision(Human* humanBoxes,ICollision* obstacleBoxes);
	bool checkHuman_ThingCollision(Human* humanBoxes,Thing* obstacleBoxes);
	bool checkHuman_EnemyCollision(Human* charcter,Human* enemy);
	void resetHuman_Collision(ICollision* resetBoxes);
	bool checkArrow_ObstacleCollision(ICollision* obstacleBoxes,ArrowBox *arrowBox);
	bool checkArrow_EnemyCollision(Human* humanBoxes,ArrowBox *arrowBox);

public:
	Collision_System();
	~Collision_System();
	void OnCheck ();
	void Load_HeroCollisions (vector<Human*>);
	void Load_EnemyCollisions (vector<Enemy*>*);
	void Load_ThingCollisions (vector<Thing*>*);
	void Load_ArrowCollisions(vector<ArrowBox*>*);
	void Add_EnemyCollisions(Enemy* enemy);
	void Del_EnemyCollisions(Enemy* enemy);
	void Load_ObstacleCollisions (vector<ICollision*>*);
	void Add_ObstacleCollisions(ICollision*);
	void Del_ObstacleCollisions(ICollision*);
	void Load_bulletCollisions (vector<ICollision*>);

};

#endif