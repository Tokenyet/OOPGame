#ifndef ICOLLISION_H
#define ICOLLISION_H
#pragma once
#include "StdAfx.h"
#include "CRectangle.h"
#include "IPerform.h"
class ICollision : public IPerform//interface
{
public:
	//virtual void SetScreenSize(int width,int height) = 0;//���󥲶����D�ثe�����j�p
	virtual CRectangle GetRect() = 0; //��i�o���C�ӳ��W�����m
	//virtual bool &GetIntersect(int) = 0;//��i�o���C�ӳ��W�����m
	virtual ~ICollision(){};
};
#endif
