#include "stdafx.h"
#include "CRectangle.h"

	CRectangle::CRectangle()
	{
		x_Left = x_Right = y_Left = y_Right = 0;
	}
	CRectangle::~CRectangle(){}
	void CRectangle::SetRectangle(int Lx,int Ly,int Rx,int Ry)
	{
		x_Left = Lx;
		y_Left = Ly;
		x_Right = Rx;
		y_Right = Ry;
	}
	bool CRectangle::Intersect(CRectangle otherRect)
	{
		bool OutSide = (x_Right < otherRect.Get_Lx() || x_Left > otherRect.Get_Rx() ||
             y_Right < otherRect.Get_Ly() || y_Left > otherRect.Get_Ry());
		    return !OutSide;
	}
	int CRectangle::Get_Lx(){return x_Left;}
	int CRectangle::Get_Ly(){return y_Left;} 
	int CRectangle::Get_Rx(){return x_Right;}
	int CRectangle::Get_Ry(){return y_Right;}