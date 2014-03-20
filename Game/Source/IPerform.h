#ifndef IPERFORM_H
#define IPERFORM_H
#pragma once
#include "ILocation.h"
class IPerform : public ILocation//interface
{
public:
	virtual void OnMove() = 0;
	virtual void OnShow() = 0;
	virtual	const int GetOriginX() = 0;
	virtual const int GetOriginY() = 0;
	virtual ~IPerform(){};
};
#endif
