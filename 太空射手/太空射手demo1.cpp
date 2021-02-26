

#include<graphics.h>
#include<tools.h>
#include "material.h"
#include"factory.h"
#include<sprite.h>
#include<list>
#define SCREEN_WIDTH    800  // size of screen
#define SCREEN_HEIGHT   600

#define BORDER_WIDTH 50
b2AABB Screen({ {0,0},{SCREEN_WIDTH-1,SCREEN_HEIGHT-1} });
b2AABB Border({ {-BORDER_WIDTH,-BORDER_WIDTH},{SCREEN_WIDTH + BORDER_WIDTH,SCREEN_HEIGHT + BORDER_WIDTH} });
/*
* 坐标系说明：由于窗口坐标系和正常坐标系存在翻转，而函数是正常坐标系下的计算
* 因此在使用诸如旋转之类的函数时要计算好坐标的对应关系在此程序中，素材的坐标
* 默认是朝上放置，相当于标准坐标系下的-PI/2，因此需要把素材旋转PI/2度，素材
* 才能指向x坐标方向.
*/





WCHAR _text[100];


// DEFINES ////////////////////////////////////////////////
HWND      main_window_handle = NULL; // globally track main window
int       window_closed = 0;    // tracks if window is closed
HINSTANCE hinstance_app = NULL; // globally track hinstance

HDC		  main_draw_hdc = NULL;
int	      fRunning = 1;
IMAGE*	  main_image;
// TYPES //////////////////////////////////////////////////////

Factory* pFac;

WCHAR buf[1020];
HFONT Default_Font;
//SpriteBody s1_fire;
//SpriteBody s1_fire2;
//SpriteBody player1;
//
//SpriteBody s2_fire;
//SpriteBody s2_fire2;
//SpriteBody player2;

Ship * Player_blue = NULL;
Ship*  m_Ship2_Orange = NULL;
Ship*  m_Ship3_Red = NULL;
std::list<Bullet*> bullet;

//LONGLONG bullet_cooling;


int Game_Init(void* parms = NULL, int num_parms = 0) {
	main_window_handle = initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	main_draw_hdc = GetImageHDC();
	main_image = GetWorkingImage();
	Screen.lowerBound = Vec2D(0, 0);
	Screen.upperBound = Vec2D((double)SCREEN_WIDTH - 1, (double)SCREEN_HEIGHT - 1);
	load_material();
	pFac = Factory::hInst();
	AddFontResource(kenvector_future);
	AddFontResource(kenvector_future_thin);
	//Default_Font = (HFONT)SelectObject(main_draw_hdc,
	//	CreateFont(0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, NAME_TO_STR(kenvector future)));
	//SelectObject(main_draw_hdc, Default_Font);
	settextcolor(RED);
	setbkmode(TRANSPARENT);

	Player_blue	   = (Ship*)pFac->Creat("Ship1_Bule");
	m_Ship2_Orange = (Ship*)pFac->Creat("Ship2_Orange");
	m_Ship3_Red    = (Ship*)pFac->Creat("Ship3_Red");

	Player_blue->main_Body.CalAABB();
	m_Ship2_Orange->main_Body.CalAABB();
	m_Ship3_Red->main_Body.CalAABB();

	Player_blue->Tran.p = { 100,100 };		Player_blue->UpdateMoTran();
	m_Ship2_Orange->Tran.p = { 100,300 };	m_Ship2_Orange->UpdateMoTran();
	m_Ship3_Red->Tran.p = { 300,100 };		m_Ship3_Red->UpdateMoTran();
	//改变喷气颜色
	Player_blue->fire_left.map = Sprite_fire_2.map;
	Player_blue->fire_right.map = Sprite_fire_2.map;
	//添加护盾
	Player_blue->shield = Sprite_shield_1;
	InsertList_front(&Player_blue->fire_left, &Player_blue->shield);

	//校准定时器
	TL::pHpte->Mark();
	//设置开火间隔
	//bullet_cooling = TL::pHpte->PrecFrequency()/15;
	return 0;
}
int Game_Shutdown(void* parms = NULL, int num_parms = 0) {
	//DeleteObject(SelectObject(main_draw_hdc, Default_Font));
	RemoveFontResource(kenvector_future);
	RemoveFontResource(kenvector_future_thin);
	
	if (Player_blue != NULL)delete Player_blue;
	if (m_Ship2_Orange != NULL)delete m_Ship2_Orange;
	if (m_Ship3_Red != NULL)delete m_Ship3_Red;
	return 0;
}
//void setbkcolor(IMAGE& Img, COLORREF color)
//{
//	IMAGE* tmep = GetWorkingImage();
//	SetWorkingImage(&Img);
//	setbkcolor(color);
//	SetWorkingImage(tmep);
//}

Vec2D p1 = { 300, 300 };
Vec2D p2 = { 300, 100 };
MOUSEMSG msg;
int Game_Main(void* parms = NULL, int num_parms = 0) {
	static int x = 0;
	static int y = 0;
	//x += clock() / 100;
	y -= 1;
	IMAGE buf;
	double sca = ((double)abs(clock() % 9000 - 4500) / 1500) / 2;
	//ScaleImage(&buf, &playerShip3_red, sca*2);
	ImgHatch(GetWorkingImage(), &Background_darkPurple, x, y);
	/*transparentimage(GetWorkingImage(), 0, 0, &playerShip3_red, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 100, 0, &playerShip2_red, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 200, 0, &playerShip1_red, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 300, 0, &ufoRed, sca, (double)clock() / 1000 * 2 * PI / 8); transparentimage(GetWorkingImage(), 300, 0, &ufoRed, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 400, 0, &enemyRed1, sca, (double)clock() / 1000 * 2 * PI / 8);

	transparentimage(GetWorkingImage(), 0, 100, &playerShip3_blue, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 100, 100, &playerShip2_blue, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 200, 100, &playerShip1_blue, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 300, 100, &ufoBlue, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 400, 100, &enemyBlue1, sca, (double)clock() / 1000 * 2 * PI / 8);

	transparentimage(GetWorkingImage(), 0, 200, &playerShip3_orange, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 100, 200, &playerShip2_orange, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 200, 200, &playerShip1_orange, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 300, 200, &ufoYellow, sca, (double)clock() / 1000 * 2 * PI / 8);
	transparentimage(GetWorkingImage(), 400, 200, &enemyBlack1, sca, (double)clock() / 1000 * 2 * PI / 8);
*/
	//绘制外观
	
	m_Ship2_Orange->Draw(GetWorkingImage());
	m_Ship3_Red->Draw(GetWorkingImage());
	for (auto iter = bullet.begin(); iter != bullet.end(); ) {
		(*iter)->Draw(GetWorkingImage());
		if ((*iter)->status == Bullet::Status::Intact) {
			(*iter)->UpdateTran();
			if (!Border.Contains((*iter)->main_Body.CalAABB((*iter)->MoTran))) {
				(*iter)->Die(TL::pHpte->getIntervals_int());
			}
			++iter;
		}
		else {
			if (TL::pHpte->getIntervals_int() - (*iter)->die_time > TL::pHpte->PrecFrequency() * 1.5) {
				delete (*iter);
				bullet.erase(iter++);
			}
			else {
				++iter;
			}
		}
		
	}
	Player_blue->Draw(GetWorkingImage());
	if (GetKeyState(VK_CAPITAL))
	{
		//绘制法线
		Player_blue->main_Body.DrawNormal(GetWorkingImage(), Player_blue->MoTran);
		m_Ship2_Orange->main_Body.DrawNormal(GetWorkingImage(), m_Ship2_Orange->MoTran);
		m_Ship3_Red->main_Body.DrawNormal(GetWorkingImage(), m_Ship3_Red->MoTran);

		//绘制AABB
		DrawAABB(Player_blue->main_Body.CalAABB(Player_blue->MoTran));
		DrawAABB(m_Ship2_Orange->main_Body.CalAABB(m_Ship2_Orange->MoTran));
		DrawAABB(m_Ship3_Red->main_Body.CalAABB(m_Ship3_Red->MoTran));

		for (auto iter = bullet.begin(); iter != bullet.end(); ) {
			(*iter++)->DrawNormal(GetWorkingImage());
		}
	}
	


	double angle = ((double)clock() / 1000 * 2 * PI / 8);
	
	if (MouseHit()) {
		msg = GetMouseMsg();
		FlushMouseMsgBuffer();
	}
	Vec2D v = Vec2D((double)msg.x, (double)msg.y);

	m_Ship2_Orange->Tran.q = Rot(-(v - m_Ship2_Orange->Tran.p).Angle()); m_Ship2_Orange->UpdateMoTran();
	Player_blue->Tran.q = Rot(-(v - Player_blue->Tran.p).Angle()); Player_blue->UpdateMoTran();
	m_Ship3_Red->Tran.q = Rot(angle); m_Ship3_Red->UpdateMoTran();
	
	if (TC::IsHit(Player_blue->main_Body.CalAABB(Player_blue->MoTran), m_Ship2_Orange->main_Body.CalAABB(m_Ship2_Orange->MoTran))
		|| TC::IsHit(Player_blue->main_Body.CalAABB(Player_blue->MoTran), m_Ship3_Red->main_Body.CalAABB(m_Ship3_Red->MoTran))
		) {
		TextOut(main_draw_hdc, 0, SCREEN_HEIGHT - 30, _text, swprintf_s(_text, L"AABB-Overlap"));
	}

	if (TC::IsHit(Player_blue->main_Body.SpriteShape, Player_blue->MoTran, m_Ship2_Orange->main_Body.SpriteShape, m_Ship2_Orange->MoTran)
		|| TC::IsHit(Player_blue->main_Body.SpriteShape, Player_blue->MoTran, m_Ship3_Red->main_Body.SpriteShape, m_Ship3_Red->MoTran)
		) {
		TextOut(main_draw_hdc, 0, SCREEN_HEIGHT - 60, _text, swprintf_s(_text, L"Hit"));
	}
	for (auto iter = bullet.begin(); iter != bullet.end(); iter++) {
		if ((*iter)->status == Bullet::Status::Intact) {
			if(TC::IsHit((*iter)->main_Body.CalAABB((*iter)->MoTran), m_Ship3_Red->main_Body.CalAABB(m_Ship3_Red->MoTran)))
			if (TC::IsHit((*iter)->main_Body.SpriteShape, (*iter)->MoTran, m_Ship3_Red->main_Body.SpriteShape, m_Ship3_Red->MoTran)) {
				(*iter)->Die(TL::pHpte->getIntervals_int());
			}
			if (TC::IsHit((*iter)->main_Body.CalAABB((*iter)->MoTran), m_Ship2_Orange->main_Body.CalAABB(m_Ship2_Orange->MoTran)))
			if (TC::IsHit((*iter)->main_Body.SpriteShape, (*iter)->MoTran, m_Ship2_Orange->main_Body.SpriteShape, m_Ship2_Orange->MoTran)) {
				(*iter)->Die(TL::pHpte->getIntervals_int());
			}
		}
		
	}
	TextOut(main_draw_hdc, SCREEN_WIDTH - 300, SCREEN_HEIGHT - 60, _text, swprintf_s(_text, L"Bullet Num:%d", (int)bullet.size()));
	TextOut(main_draw_hdc, SCREEN_WIDTH - 300, SCREEN_HEIGHT - 40, _text, swprintf_s(_text, L"Game time:%lfs", TL::pHpte->getIntervals_db()));

	if (KEYDOWN(49)) {
		RemoveList(&Player_blue->damage);
		Player_blue->damage = Sprite_Ship1_damage1;
		InsertList_front(&Player_blue->fire_left, &Player_blue->damage);
	}if (KEYDOWN(50)) {
		RemoveList(&Player_blue->damage);
		Player_blue->damage = Sprite_Ship1_damage2;
		InsertList_front(&Player_blue->fire_left, &Player_blue->damage);
	}if (KEYDOWN(51)) {
		RemoveList(&Player_blue->damage);
		Player_blue->damage = Sprite_Ship1_damage3;
		InsertList_front(&Player_blue->fire_left,  & Player_blue->damage);
	}if (KEYDOWN(52)) {
		RemoveList(&Player_blue->damage);
		/*Player_blue->damage = Sprite_Ship1_damage3;
		ConnectList(&Player_blue->damage, &Player_blue->fire_left);*/
	}
	if (KEYDOWN(53)) {
		RemoveList(&Player_blue->shield);
		Player_blue->shield = Sprite_shield_1;
		InsertList_front(&Player_blue->fire_left, &Player_blue->shield);
	}if (KEYDOWN(54)) {
		RemoveList(&Player_blue->shield);
		Player_blue->shield = Sprite_shield_2;
		InsertList_front(&Player_blue->fire_left, &Player_blue->shield);
	}if (KEYDOWN(55)) {
		RemoveList(&Player_blue->shield);
		Player_blue->shield = Sprite_shield_3;
		InsertList_front(&Player_blue->fire_left, &Player_blue->shield);
	}if (KEYDOWN(56)) {
		RemoveList(&Player_blue->shield);
		/*Player_blue->damage = Sprite_Ship1_damage3;
		ConnectList(&Player_blue->damage, &Player_blue->fire_left);*/
	}if (KEYDOWN(112)) {
		TL::pHpte->Pause();
	}
	if (KEYDOWN(113)) {
		TL::pHpte->Continue();
	}if (KEYDOWN(32)) {
		Player_blue->fire(bullet);
		//bullet_cooling
		//static LONGLONG lastfire = 0;
		//if (TL::pHpte->getIntervals_int() - lastfire > bullet_cooling) {
		//	lastfire = TL::pHpte->getIntervals_int();
		//	Bullet* temp = (Bullet*)pFac->Creat("Bullet_laserBlue01");
		//	temp->Tran = Player_blue->Tran; temp->UpdateMoTran();
		//	//temp->tran.q = Mul(Player_blue->tran.q, Rot(PI / 2));
		//	temp->velocity = 5;
		//	//temp->die_Body.map.SetIFS(TL::pHpte->PrecFrequency() / 8);
		//	temp->main_Body.CalAABB();
		//	bullet.push_front(temp);
		//}
	}


	if (KEYDOWN(83))Player_blue->Tran.p.y += 3;
	if (KEYDOWN(87))Player_blue->Tran.p.y -= 3;
	if (KEYDOWN(68))Player_blue->Tran.p.x += 3;
	if (KEYDOWN(65))Player_blue->Tran.p.x -= 3;
	Player_blue->UpdateMoTran();
	/*Vec2D v(100, 0);
	v.RotateT(Rot((double)clock() / 1000 * 2 * PI / 8));
	setfillcolor(WHITE);
	v += {300, 300};
	fillcircle(300, 300, 2);
	fillcircle((int)v.x, (int)v.y, 2);
	setfillcolor(RED);
	fillcircle(300, 300, 2);*/
	return 0;
}
int _main()
{
	Game_Init();
	//Game_Init();
	BeginBatchDraw();
	while (fRunning) {
		cleardevice();
		fRunning = !Game_Main();

		SaveDC(main_draw_hdc);
		settextcolor(RED);
		TextOut(main_draw_hdc, SCREEN_WIDTH -16*8, 0, _text, swprintf_s(_text, L"FPS:%d", TL::Get_Fps_t(1)));
		RestoreDC(main_draw_hdc,-1);
	/*	TextOut(main_draw_hdc, SCREEN_WIDTH - 16 * 3 - 8*4, 0, L"", 4);*/
		FlushBatchDraw();
		TL::FraCtrl(60);
	}
	EndBatchDraw();
	Game_Shutdown();
	return 0;
}