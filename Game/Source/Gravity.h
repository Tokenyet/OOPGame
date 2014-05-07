#ifndef GRAVITY_H
#define GRAVITY_H


class Gravity
{
private:
	int *sync_y;
	bool trigger_upMove;
	double interval_time;
	double timeUpLimit;
	double timeNow,timePast;
	void resetTimeParameter(bool JumpOrFall);
	int gravity(double Vo,double g,double Time,double PriTime);
	void jumpUptimeParameter(bool);
	bool isOnGround,isOnSky,isKeepUpMove;
public:
	Gravity(int*);
	~Gravity();
	bool GetOnGround();
	bool GetOnSky();
	bool GetKeepUpMove();
	void SetOnGround(bool);
	void SetOnSky(bool);
	void SetKeepUpMove(bool);
	void Falling();
	bool Dojump(bool);
	void Jumping();

};

#endif