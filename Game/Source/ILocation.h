#ifndef ILOCATION_H
#define ILOCATION_H
#pragma once
class ILocation//interface
{
public:
	//virtual void SetScreenSize(int width,int height) = 0;//���󥲶����D�ثe�����j�p
	virtual int &GetX() = 0; //��i�o���C�ӳ��W�����m
	virtual int &GetY() = 0;//��i�o���C�ӳ��W�����m
	virtual ~ILocation(){};
};
#endif
