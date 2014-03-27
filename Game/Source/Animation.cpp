#include "StdAfx.h"
#include "Animation.h"
#include <string>

void Animation::StateInitialize()
{
	myState = R_Walking;
	Reset();
}

void Animation::SetTopLeft(int x,int y)
{
	animations[myState].SetTopLeft(x,y);
}

void Animation::OnMove(Animax_act action)
{
	if(action != myState)
	{
		animations[myState].Reset();
		myState = action;
	}
	animations[myState].OnMove();
}
	
void Animation::OnShow()
{
	animations[myState].OnShow();
}

void Animation::LoadAnimation(Animax_act action,char* path)
{
	/*game_framework::CAnimation *newAnimationLoad = new game_framework::CAnimation(10);
	newAnimationLoad->AddBitmap(path,RGB(255,255,255));*/
	animations[action].AddBitmap(path,RGB(0,0,0));
	//animations.insert(map<Animax_act,game_framework::CAnimation>::value_type(action,newAnimationLoad));
}

void Animation::LoadAnimation(Animax_act action,char* paths[],int pic_amout)
{
	for(int i = 0;i<pic_amout;i++)
		LoadAnimation(action,paths[i]);
/*		newAnimationLoad.AddBitmap(*paths[i],RGB(255,255,255));
	animations.insert(pair<Animax_act,game_framework::CAnimation>(action,newAnimationLoad));*/
}

int Animation::Height()
{
	return animations[myState].Height();
}
int Animation::Width()
{
	return animations[myState].Width();
}

void Animation::Reset()
{
	 map <Animax_act,game_framework::CAnimation>::iterator animaAction;
	 for ( animaAction = animations.begin( ); animaAction != animations.end( ); animaAction++ )
	 {
		 animaAction -> second.Reset();
		animaAction -> second.SetDelayCount(5);
	 }
}