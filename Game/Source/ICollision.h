#ifndef ICOLLISION_H
#define ICOLLISION_H
#pragma once
#include "StdAfx.h"
#include "CRectangle.h"
#include "IPerform.h"
class ICollision : public IPerform//interface
{
public:
	//virtual void SetScreenSize(int width,int height) = 0;//物件必須知道目前視窗大小
	virtual CRectangle GetRect() = 0; //方可得知每個場上物件位置
	virtual bool &GetIntersect(int) = 0;//方可得知每個場上物件位置
	virtual ~ICollision(){};
};
#endif
