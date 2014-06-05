/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	/*logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();*/
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(SIZE_X/3,SIZE_Y/3,"Please Enter to Start.");
	pDC->TextOut(SIZE_X/20,SIZE_Y-50,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(SIZE_X/20,SIZE_Y-100,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(SIZE_X/20,SIZE_Y-150,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
/*	for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��*/
	/*CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI*/
}

void CGameStateRun::OnMove()							// ���ʹC������
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
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// ���ʭI���Ϫ��y��
	//
	/*if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// ���ʲy
	//
	int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();*/
	//
	// �������l
	//
	//eraser.OnMove();
	//
	// �P�_���l�O�_�I��y
	//
	/*for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}*/
	//
	// ���ʼu�����y
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

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
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
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	/*help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	corner.ShowBitmap(background);							// �Ncorner�K��background
	bball.LoadBitmap();										// ���J�ϧ�
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid*/
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
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
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(true);
	/*int offset = charcter->GetX() - SIZE_X/2 +50;
	icollisions_obs.push_back(new Obstacle(point.x + offset,point.y));
	scroll_System.AddObject(icollisions_obs[icollisions_obs.size()-1]);
	scroll_System.OnMove();
	collision_System.Load_ObstacleCollisions(icollisions_obs);*/
	level_Editor.LMouseOnClick(true,point);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	level_Editor.RMouseOnClick(true,point);
	//eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{

	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	//background.ShowBitmap();			// �K�W�I����
	//help.ShowBitmap();					// �K�W������
	//cgamemap.OnShow();
	//hits_left.ShowBitmap();
	/*for (int i=0; i < NUMBALLS; i++)
		ball[i].OnShow();				// �K�W��i���y
	bball.OnShow();		*/				// �K�W�u�����y
	//eraser.OnShow();					// �K�W���l
	//
	//  �K�W���W�Υk�U��������
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
	
	/*charcter->OnShow();
	enemytest->OnShow();*/
}

}
