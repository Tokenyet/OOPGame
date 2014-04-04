#ifndef ITEMS_H
#define ITEMS_H
#include "Enemy.h"
#include "Obstacle.h"

enum ObjectData
{
	ColBlock = 0,//"Bitmaps/block-5.bmp"
	RowBlock = 1,//"Bitmaps/block-4.bmp"
	MushRoom = 3,//"Bitmaps/l_mushroom.bmp"
};


class Items
{
private:
	vector<ObjectData> recorders;
	vector<string> stringData;
	vector<Obstacle*> obstacles;
	vector<Enemy*> enemys;
	Obstacle *delete_Obstacle_Temp;
	Enemy *delete_Enemy_Temp;
	bool DelObstacle(int recorder_index,int object_index,int x,int y,int offset);
	bool DelEnemy(int recorder_index ,int object_index,int x,int y,int offset);
public:
	bool Check_and_Delete_Object_On_Position(int x,int y,int offset);
	void Add(Obstacle*);
	void Add(Enemy*);
	Obstacle * GetObstacleTemp();
	Enemy *GetEnemyTemp();
	vector<Obstacle*>& GetObstacles_element();
	vector<Enemy*>& GetEnemys_element();
	vector<string> GetStringData();

};

#endif