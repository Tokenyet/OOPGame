#include "StdAfx.h"
#include "Ewalk.h"



void Nomal_Walking::Walk(int &x,int&y,bool &r_Restrict,bool &l_Restrict
						,int r_x,int l_x,int speed,int width,HeadDirection &direction)
{
	AI(x,r_Restrict,l_Restrict,r_x,l_x,speed,width,direction);
}

//¥ª¥k¨«Strategy
	void Nomal_Walking::AI(int &x,bool &r_Restrict,bool &l_Restrict,int r_x,int l_x,int speed,int width,HeadDirection &direction)
	{
		if(direction == Head_Right)
		{
			if(r_Restrict)
			{
				if(x + width >= r_x + speed)
				{
					leftWalking(x,l_Restrict,l_x,speed);
					direction = Head_Left;
				}
			}
			else
				rightWalking(x,r_Restrict,r_x,speed,width);
		}
		else
		{
			if(l_Restrict)
			{
				if(x + width >= r_x + speed)
				{
					rightWalking(x,r_Restrict,r_x,speed,width);
					direction = Head_Right;
				}
			}
			else
				leftWalking(x,l_Restrict,l_x,speed);
		}
	}
	void Nomal_Walking::leftWalking(int &x,bool &l_Restrict,int l_x,int speed)
	{
		if(l_Restrict)
		{
			if(!(x <= l_x)) // SIZE_X/2-50 <= leftBoundedValue
				x -= speed;
		}
		else
			x-=speed;

			/*else
				x -= speed;*/
	}
	void Nomal_Walking::rightWalking(int &x,bool &r_Restrict,int r_x,int speed,int width)
	{
		if(r_Restrict)
		{
			if(!(x + width>= r_x))//SIZE_X/2-50 >= rightBoundedValue
				x += speed;
		}
		else
		{
			x+= speed;
		}
			/*else
				x += speed;*/
	}