#pragma once
#include<graphics.h>
#include<tools.h>
#include "material.h"
#include"factory.h"
#include<sprite.h>
#include<list>

class World {
public:
	World() {};
	Ship* Player_blue = NULL;
	Ship* m_Ship2_Orange = NULL;
	Ship* m_Ship3_Red = NULL;
	//Ship* Player_Ship = NULL;
	Factory* pFac = NULL;
	IMAGE* pOutImg = NULL;
	HDC pOutHDC = NULL;
	WCHAR _text[100] = {0};
	bool isPutEnemy = false;
	MOUSEMSG msg;
	~World();
	void PlayerRebirth(const char* ShipName);
	void CameraDraw(IMAGE* ImgDst);
	void ControlInput();
	void Collision();
	void WorldUpdate();

	//Running the world,just need call Init,Main
	void Init();
	int  Main() {
		WorldUpdate();
		return isRun;
	}
	bool isRun = true;
	//Camera代表屏幕窗口
	int CameraWidth = 640;
	int CameraHeight = 480;
	int CameraBorderWidth = 150;
	Vec2D  CameraSite;//摄像机坐标
	//Vec2D  WorldSite;
	//自动更新
	b2AABB CameraAABB;
	b2AABB CameraBorderAABB;

	std::list<Ship*> Ships;
	std::list<Bullet*> Bullets;
};
