#include "StdAfx.h"
#include "Bounding_Obs.h"

//人物對障礙物用碰撞偵測

	Bounding_Obs::Bounding_Obs(){}
	Bounding_Obs::~Bounding_Obs(){}

	void Bounding_Obs::SetOriginRectangle(int lx,int ly,int width,int height,int detect_range = 0)
	{
		originRect.SetRectangle(lx+2*detect_range, ly+2*detect_range, width-4*detect_range, height-4*detect_range);
		rowRect.SetRectangle(lx-detect_range, ly, width+2*detect_range, height);
		colRect.SetRectangle(lx, ly-detect_range, width, height+ 2*detect_range);
	}
	bool Bounding_Obs::LeftIntersect(CRectangle obstacleBox)
	{
		if(rowRect.Intersect(obstacleBox))//左邊碰撞成功
			if(originRect.Get_Lx()  > obstacleBox.Get_Rx() && obstacleBox.Get_Rx() > rowRect.Get_Lx()) //人在物體的左方
				return true;
		return false;
	}
	bool Bounding_Obs::RightIntersect(CRectangle obstacleBox)
	{
		if(rowRect.Intersect(obstacleBox))//右邊碰撞成功
			if(rowRect.Get_Rx() > obstacleBox.Get_Lx() && obstacleBox.Get_Lx() > originRect.Get_Rx()) //人在物體右方
				return true;
		return false;
	}
	bool Bounding_Obs::DownIntersect(CRectangle obstacleBox)//下盤碰撞成功
	{
		if(colRect.Intersect(obstacleBox))
			if(colRect.Get_Ry() > obstacleBox.Get_Ly() && obstacleBox.Get_Ly() > originRect.Get_Ry()) //人在物體上方
				return true;
		return false;
	}
	bool Bounding_Obs::UpIntersect(CRectangle obstacleBox)//上身碰撞成功
	{
		if(colRect.Intersect(obstacleBox))
			if(originRect.Get_Ly() > obstacleBox.Get_Ry() && obstacleBox.Get_Ry() > colRect.Get_Ly()) //人在物體的下方
				return true;
		return false;
	}
	CRectangle Bounding_Obs::GetRowRect()
	{
		return  rowRect;
	}
	CRectangle Bounding_Obs::GetColRect()
	{
		return colRect;
	}
	CRectangle Bounding_Obs::GetOriginRect()
	{
		return originRect;
	}

	int Bounding_Obs::GetWidth()
	{
		return originRect.Get_Width();
	}
	int Bounding_Obs::GetHeight()
	{
		return originRect.Get_Heigth();
	}
