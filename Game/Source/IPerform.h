#pragma once
class IPerform : public ILocation//interface
{
public:
	virtual void OnMove() = 0;
	virtual void OnShow() = 0;
	virtual ~IPerform(){};
};
