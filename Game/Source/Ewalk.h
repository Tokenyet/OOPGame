#ifndef EWALK_H
#define EWALK_H

enum HeadDirection
{
	Head_Left,
	Head_Right,
};

class Ewalk //interface
{
public:
	virtual void Walk(int &x,int&y,bool &r_Restrict,bool &l_Restrict,int r_x,int l_x,int speed,int width,HeadDirection &direction) = 0;
};

class Nomal_Walking : public  Ewalk//implement
{
protected:
	void leftWalking(int &x,bool &l_Restrict,int l_restric_x,int speed);
	void rightWalking(int &x,bool &r_Restrict,int r_restric_x,int speed,int width);
	void AI(int &x,bool &r_Restrict,bool &l_Restrict,int r_x,int l_x,int speed,int width,HeadDirection &direction);
public:
	void Walk(int &x,int&y,bool &r_Restrict,bool &l_Restrict,int r_x,int l_x,int speed,int width,HeadDirection &direction);

};
#endif
