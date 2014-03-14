#pragma once
class ILocation//interface
{
public:
	//virtual void SetScreenSize(int width,int height) = 0;//物件必須知道目前視窗大小
	virtual int &GetX() = 0; //方可得知每個場上物件位置
	virtual int &GetY() = 0;//方可得知每個場上物件位置
	virtual ~ILocation(){};
};
