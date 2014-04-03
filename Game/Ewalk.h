#ifndef EWALK_H
#define EWALK_H

class Ewalk //interface
{
public:
	virtual void Walk(int &x,int&y,bool &r_Restrict,bool &l_Restrict,int r_x,int l_y);
};
class Nomal_Walking : public  Ewalk//implement
{
public:
	void Walk(int &x,int&y,bool &r_Restrict,bool &l_Restrict,int r_x,int l_y);
};
#endif
