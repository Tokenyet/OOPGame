#include "StdAfx.h"
#include "Bounding_Obs.h"

//人物對障礙物用碰撞偵測

	void Bounding_Obs::SetOriginRectangle(int lx,int ly,int width,int height,int detect_range)
	{
		originRect.SetRectangle(lx, ly, width, height);
		rowRect.SetRectangle(lx-detect_range, ly, width+2*detect_range, height);
		colRect.SetRectangle(lx, ly-detect_range, width, height+ 2*detect_range);
	}
	bool Bounding_Obs::RightIntersect(CRectangle obstacleBox)
	{
		if(rowRect.Intersect(obstacleBox))
			if(originRect.Get_Lx() > obstacleBox.Get_Rx() && obstacleBox.Get_Rx() > rowRect.Get_Lx()) //人在物體的左方
				return true;
		return false;
	}
	bool Bounding_Obs::LeftIntersect(CRectangle obstacleBox)
	{
		if(rowRect.Intersect(obstacleBox))
			if(originRect.Get_Rx() > obstacleBox.Get_Lx() && obstacleBox.Get_Lx() > rowRect.Get_Rx()) //人在物體右方
				return true;
		return false;
	}
	bool Bounding_Obs::UpIntersect(CRectangle obstacleBox)
	{
		if(colRect.Intersect(obstacleBox))
			if(colRect.Get_Ly() > obstacleBox.Get_Ry() && obstacleBox.Get_Ry() > originRect.Get_Ly()) //人在物體上方
				return true;
		return false;
	}
	bool Bounding_Obs::DownIntersect(CRectangle obstacleBox)
	{
		if(rowRect.Intersect(obstacleBox))
			if(colRect.Get_Ry() > obstacleBox.Get_Ly() && obstacleBox.Get_Ly() > originRect.Get_Ry()) //人在物體的下方
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
