#include "StdAfx.h"
#include "Items.h"
#include "Enemy.h"
#include "Obstacle.h"

bool Items::Check_and_Delete_Object_On_Position(int x,int y,int offset)
{
	int obstacle_index = 0;
	int enemy_index = 0;
	for(size_t i = 0;i<recorders.size();i++)
	{
		switch(recorders[i])
		{
			case ColBlock:
			case RowBlock:
				if(obstacles.empty())
					break;
				if(obstacles[obstacle_index])
					if(DelObstacle(i,obstacle_index,x,y,offset))
						return true;
				obstacle_index++;
				break;
			case MushRoom:
				if(enemys.empty())
					break;
				if(enemys[enemy_index])
					if(DelEnemy(i,enemy_index,x,y,offset))
						return true;
					enemy_index++;
				break;
			default:
				ASSERT(0);
				break;
		}
	}
	return false;
}

bool Items::DelObstacle(int recorder_index,int object_index,int x,int y,int offset)
{
	 x += offset;
	if(x < obstacles[object_index]->GetOriginX() + obstacles[object_index]->GetRect().Get_Width()&&
		y < obstacles[object_index]->GetRect().Get_Ry()&&
		x > obstacles[object_index]->GetOriginX()&&
		y > obstacles[object_index]->GetRect().Get_Ly())
			{
			   delete_Obstacle_Temp = obstacles[object_index];
			   obstacles.erase(obstacles.begin()+object_index);
			   recorders.erase(recorders.begin()+recorder_index);
			   stringData.erase(stringData.begin()+recorder_index);
			   return true;
			}
	delete_Obstacle_Temp = NULL;
	return false;

}

bool Items::DelEnemy(int recorder_index ,int object_index,int x,int y,int offset)
{
	int width = enemys[object_index]->GetRect().GetWidth();
	int heigth = enemys[object_index]->GetRect().GetHeight();
	if(x < enemys[object_index]->GetX() + width&&
		y < enemys[object_index]->GetY() + heigth&&
		x > enemys[object_index]->GetX()&&
		y > enemys[object_index]->GetY())
	{
			   delete_Enemy_Temp = enemys[object_index];
			   enemys.erase(enemys.begin()+object_index);
			   recorders.erase(recorders.begin()+recorder_index);
			   stringData.erase(stringData.begin()+recorder_index);
			   return true;
	}
	delete_Enemy_Temp = NULL;
	return false;
}


void Items::Add(Obstacle* obstacle)
{
	obstacles.push_back(obstacle);
}
void Items::Add(Enemy* enemy)
{
	enemys.push_back(enemy);
}
vector<Obstacle*>& Items::GetObstacles_element()
{
	return obstacles;
}
vector<Enemy*>& Items::GetEnemys_element()
{
	return enemys;
}
vector<string> Items::GetStringData()
{
	return stringData;
}
Obstacle * Items::GetObstacleTemp()
{
	return delete_Obstacle_Temp;
}
Enemy * Items::GetEnemyTemp()
{
	return delete_Enemy_Temp;
}