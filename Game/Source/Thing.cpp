#include "stdafx.h"
#include "Thing.h"
#include <WinDef.h>

	int& Thing::GetX(){ return x;}
	int& Thing::GetY(){ return y;}
	void Thing::OnMove(){}
	void Thing::OnShow(){}
	void Thing::LoadBitmap(char *,COLORREF RGB){}