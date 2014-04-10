#ifndef ANIMATION_H
#define ANIMATION_H
#include <ddraw.h>
#include "gamelib.h"

enum Animax_act
{
	LStanding = 0,
	RStanding = 1,
	L_Walking = 2,
	R_Walking = 3,
	L_Jumping = 4,
	R_Jumping = 5,
	L_Attacking = 6,
	R_Attacking = 7,
};

class Animation
{
private:
	Animax_act myState;
	map<Animax_act,game_framework::CAnimation> animations;
	void AddAnimation(Animax_act,string);
public:
	void StateInitialize();
	void SetTopLeft(int x,int y);
	void OnShow();
	void OnMove(Animax_act);
	void LoadAnimation(Animax_act,char*);
	void LoadAnimation(Animax_act,char** paths,int pic_amount);
	void LoadAnimation(Animax_act,char*,int keyBlackorWhite);
	void LoadAnimation(Animax_act,char** paths,int pic_amount,int keyBlackorWhite);
	void Reset();
	int Height();
	int Width();
	Animax_act GetNowState();
};
#endif
