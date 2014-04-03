#ifndef EGRAVITY_H
#define EGRAVITY_H

class EGravity //interface
{
public:
	virtual void JumpOrFall(int&y,bool &u_Restrict,bool &d_Restrict
		,int u_y,int d_y,double &time_restriction,double &timeNow,double &timePast
		,double interval_time,int heigth,bool canJump) = 0;
};

class Normal_Gravity : public  EGravity//implement
{
protected:
//	void Jumping(int &y,bool &u_Restrict,int u_restric_y);
	/*void AI(int&y,bool &u_Restrict,bool &d_Restrict
		,int u_y,int d_y,int time_restriction,int timeNow,int timePast,int interval_time,int heigth,bool canJump);*/
	bool isOnGround;
	void Dropping(int &y,bool &d_Restrict,int d_restric_y,double &timeNow,double &timePast,double interval_time,int heigth);
	int gravity(double Vo,double g,double Time,double PriTime);
	void resetTimeParameter(double &timeNow,double &timePast);
public:
	void JumpOrFall(int&y,bool &u_Restrict,bool &d_Restrict
		,int u_y,int d_y,double &time_restriction,double &timeNow,double &timePast,double interval_time,int heigth,bool canJump);

};
#endif
