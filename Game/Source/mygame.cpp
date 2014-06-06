/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <vector>

#include "ILocation.h"
#include "IPerform.h"
#include "Map.h"
#include "ScreenMap.h"
#include "Scroll_System.h"
#include "Collision_System.h"
#include "Obstacle.h"
#include "Thing.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Human.h"
#include "Charcter.h"
#include "LevelEditor.h"
#include "SkillSets.h"


namespace game_framework {



CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	const char KEY_ENTER = 0x0D;
	if (nChar == KEY_ENTER)
		GotoGameState(GAME_STATE_RUN);	
	else if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	/*logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();*/
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(SIZE_X/3,SIZE_Y/3,"Please Enter to Start.");
	pDC->TextOut(SIZE_X/20,SIZE_Y-50,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(SIZE_X/20,SIZE_Y-100,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(SIZE_X/20,SIZE_Y-150,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);

}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g)/*, NUMBALLS(28)*/
{
	charcter = new Charcter();
	obtest = new Obstacle(200,200);
	rowObtest = new Obstacle(300,300);
	enemytest = new Enemy(300,100,Type_MushRoom);
	testX = testY = 0;

	//thingTests = new vector<Thing*>();
	/*thingtest = new Thing(400,400);
	thingTests->push_back(thingtest);*/
	/*ball = new CBall [NUMBALLS];*/
}

CGameStateRun::~CGameStateRun()
{
	delete charcter;
	iperforms_obs.clear();
	icollisions_obs.clear();
	humans.clear();
//	delete [] ball;
	//for(size_t i=0;i<iperforms_obs.size();i++)
		//iperforms_obs.clear();

/*	for(size_t i=0;i<icollisions_obs.size();i++)
	delete icollisions_obs[i];*/

/*	for(size_t i=0;i<humans.size();i++)
	delete humans[i];*/

/*	for(size_t i=0;i<enemys->size();i++)
	delete (*enemys)[i];
	for(size_t i=0;i<obstacles->size();i++)
	delete (*obstacles)[i];
*/	

	delete obtest;

	delete rowObtest;

	delete enemytest;

}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;

	game_framework::CAudio::Instance()->Play(0,true);
/*	for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標*/
	/*CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI*/
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//practice.SetTopLeft(10,10);
	/*if(picX <= SIZE_Y){
		picX += 5;
		picY += 5;
	}
	else
		picX = picY = 0;
	practice.SetTopLeft(picX,picY);
	cpractice.OnMove();*/
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 移動背景圖的座標
	//
	/*if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// 移動球
	//
	int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();*/
	//
	// 移動擦子
	//
	//eraser.OnMove();
	//
	// 判斷擦子是否碰到球
	//
	/*for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}*/
	//
	// 移動彈跳的球
	//
	/*bball.OnMove();
	cgamemap.OnMove();*/
	/*testY--;
	if(testY < 0-SIZE_Y)
		testY = 0;
	map.SetMapLocation(0,testY);*/
	//screenMap.OnMove();
	//obtest->OnMove();

	collision_System.OnCheck();
	/*charcter->OnMove();
	enemytest->OnMove();*/
	for(size_t i = 0;i<enemys->size();i++)
		(*enemys)[i]->OnMove();
	for(size_t i = 0;i<humans.size();i++)
		humans[i]->OnMove();
	skillSets.OnMove();
	for(size_t i = 0;i<thingTests->size();i++)
		(*thingTests)[i]->OnMove();
	for(size_t i = 0;i<arrowBoxes.size();i++)
		arrowBoxes[i]->OnMove();
	scroll_System.OnMove();
	/*charcter->ResetRestriction();
	enemytest->ResetRestriction();*/
	for(size_t i = 0;i<humans.size();i++)
		humans[i]->ResetRestriction();
	for(size_t i = 0;i<enemys->size();i++)
		(*enemys)[i]->ResetRestriction();

	if(charcter->GetRestartGame())
	{
		GotoGameState(GAME_STATE_OVER);
		reset();
	}
}

void CGameStateRun::reset()
{
	//enemytest->LoadBitmapA();
	level_Editor.Reset();
	iperforms_obs.clear();
	icollisions_obs.clear();
	humans.clear();
	enemys = level_Editor.GetEnemysDatas();
	vector<Obstacle*> *data_Obstacle = level_Editor.GetObstaclsDatas();
	for(size_t i = 0;i<data_Obstacle->size();i++)
	{
		iperforms_obs.push_back((*data_Obstacle)[i]);
		icollisions_obs.push_back((*data_Obstacle)[i]);
	}
	humans.push_back(charcter);
	for(size_t i = 0;i<humans.size();i++)
		humans[i]->Reset();

	collision_System.Load_EnemyCollisions(enemys);
	collision_System.Load_HeroCollisions(humans);
	collision_System.Load_ObstacleCollisions(&icollisions_obs);
	scroll_System.LoadEnemy(enemys);
	scroll_System.Initialize(&iperforms_obs);
	scroll_System.SetCharcter(charcter);

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	obtest->LoadBitmapA("Bitmaps/block-5.bmp");
	rowObtest->LoadBitmap("Bitmaps/block-4.bmp");
	//enemytest->LoadBitmapA();
	charcter->LoadBitmapA();
	skillSets.Initialization(charcter,&arrowBoxes);
	level_Editor.Initialization(&scroll_System,&collision_System,charcter);
	vector<Obstacle*> *data_Obstacle = level_Editor.GetObstaclsDatas();
	for(size_t i = 0;i<data_Obstacle->size();i++)
	{
		iperforms_obs.push_back((*data_Obstacle)[i]);
		icollisions_obs.push_back((*data_Obstacle)[i]);
	}
	//iperforms_obs.push_back(thingtest);//***
	enemys = level_Editor.GetEnemysDatas();
	humans.push_back(charcter);

	thingTests = level_Editor.GetThingsDatas();
	for(size_t i = 0;i<thingTests->size();i++)
		iperforms_obs.push_back((*thingTests)[i]);


	collision_System.Load_ThingCollisions(thingTests);
	collision_System.Load_EnemyCollisions(enemys);
	collision_System.Load_HeroCollisions(humans);
	collision_System.Load_ObstacleCollisions(&icollisions_obs);
	collision_System.Load_ArrowCollisions(&arrowBoxes);
	scroll_System.LoadEnemy(enemys);
	scroll_System.LoadArrows(&arrowBoxes);
	//scroll_System.AddEnemy(enemytest);
	/*scroll_System.AddEnemy(enemys);*/
	scroll_System.Initialize(&iperforms_obs);
	scroll_System.SetCharcter(charcter);
	game_framework::CAudio::Instance()->Load(0,  "sounds\\bgm.mp3");
	game_framework::CAudio::Instance()->Load(1,  "sounds\\player-jump.mp3");
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	/*help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	corner.ShowBitmap(background);							// 將corner貼到background
	bball.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid*/
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_ENTER = 0x0D;
	//cgamemap.OnKeyDown(nChar);
/*	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(true);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(true);*/
	//screenMap.SetKeyDownControl(nChar);


	if(nChar == KEY_ENTER)
	{
		GotoGameState(GAME_STATE_OVER);
		reset();
	}
	scroll_System.KeyDownUpdate(nChar);
	charcter->KeyDownDetect(nChar);
	level_Editor.KeyDownChange(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	/*if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);*/
	//screenMap.SetKeyUpControl(nChar);
	scroll_System.KeyUpUpdate(nChar);
	charcter->KeyUpDetect(nChar);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingLeft(true);
	/*int offset = charcter->GetX() - SIZE_X/2 +50;
	icollisions_obs.push_back(new Obstacle(point.x + offset,point.y));
	scroll_System.AddObject(icollisions_obs[icollisions_obs.size()-1]);
	scroll_System.OnMove();
	collision_System.Load_ObstacleCollisions(icollisions_obs);*/
	level_Editor.LMouseOnClick(true,point);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	level_Editor.RMouseOnClick(true,point);
	//eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{

	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	//background.ShowBitmap();			// 貼上背景圖
	//help.ShowBitmap();					// 貼上說明圖
	//cgamemap.OnShow();
	//hits_left.ShowBitmap();
	/*for (int i=0; i < NUMBALLS; i++)
		ball[i].OnShow();				// 貼上第i號球
	bball.OnShow();		*/				// 貼上彈跳的球
	//eraser.OnShow();					// 貼上擦子
	//
	//  貼上左上及右下角落的圖
	//
	/*corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();*/
	/*practice.ShowBitmap();
	cpractice.OnShow();*/
	//map.OnShow();
	//screenMap.OnShow();
	scroll_System.OnShowMap();
	//obtest->OnShow();
	/*for(size_t i = 0;i<icollisions_obs.size();i++)
		icollisions_obs[i]->OnShow();*/
	level_Editor.TestShowObjects();
	for(size_t i = 0;i<enemys->size();i++)
		(*enemys)[i]->OnShow();
	for(size_t i = 0;i<humans.size();i++)
		humans[i]->OnShow();
	for(size_t i = 0;i<thingTests->size();i++)
		(*thingTests)[i]->OnShow();
	for(size_t i = 0;i<arrowBoxes.size();i++)
		arrowBoxes[i]->OnShow();
			// 取得 Back Plain 的 CDC 


	/*charcter->OnShow();
	enemytest->OnShow();*/
}

}
