#include "factory.h"
#include <thread>
#include <vector>
//机体
SpriteBody Sprite_Ship1_blue;
SpriteBody Sprite_Ship1_green;
SpriteBody Sprite_Ship1_orange;
SpriteBody Sprite_Ship1_red;
SpriteBody Sprite_Ship2_blue;
SpriteBody Sprite_Ship2_green;
SpriteBody Sprite_Ship2_orange;
SpriteBody Sprite_Ship2_red;
SpriteBody Sprite_Ship3_blue;
SpriteBody Sprite_Ship3_green;
SpriteBody Sprite_Ship3_orange;
SpriteBody Sprite_Ship3_red;
SpriteBody Sprite_ufoBlue;
SpriteBody Sprite_ufoGreen;
SpriteBody Sprite_ufoRed;
SpriteBody Sprite_ufoYellow;
//战损
SpriteBody Sprite_Ship1_damage1;
SpriteBody Sprite_Ship1_damage2;
SpriteBody Sprite_Ship1_damage3;
SpriteBody Sprite_Ship2_damage1;
SpriteBody Sprite_Ship2_damage2;
SpriteBody Sprite_Ship2_damage3;
SpriteBody Sprite_Ship3_damage1;
SpriteBody Sprite_Ship3_damage2;
SpriteBody Sprite_Ship3_damage3;
//喷气，向下
SpriteBody Sprite_fire_1;
SpriteBody Sprite_fire_2;
SpriteBody Sprite_fire_3;
//向上
SpriteBody Sprite_fire_4;
SpriteBody Sprite_fire_5;
SpriteBody Sprite_fire_6;

SpriteBody Sprite_shield_1;
SpriteBody Sprite_shield_2;
SpriteBody Sprite_shield_3;

//激光
SpriteBody Sprite_laserBlue01;


//激光爆炸
SpriteBody Sprite_laserflareBlue01;


//Enemies
SpriteBody Sprite_enemyBlack1;
SpriteBody Sprite_enemyBlack2;
SpriteBody Sprite_enemyBlack3;
SpriteBody Sprite_enemyBlack4;
SpriteBody Sprite_enemyBlack5;

SpriteBody Sprite_enemyBlue1;
SpriteBody Sprite_enemyBlue2;
SpriteBody Sprite_enemyBlue3;
SpriteBody Sprite_enemyBlue4;
SpriteBody Sprite_enemyBlue5;

SpriteBody Sprite_enemyGreen1;
SpriteBody Sprite_enemyGreen2;
SpriteBody Sprite_enemyGreen3;
SpriteBody Sprite_enemyGreen4;
SpriteBody Sprite_enemyGreen5;

SpriteBody Sprite_enemyRed1;
SpriteBody Sprite_enemyRed2;
SpriteBody Sprite_enemyRed3;
SpriteBody Sprite_enemyRed4;
SpriteBody Sprite_enemyRed5;


//Explosion
SpriteBody Sprite_expl_01;//64*64
SpriteBody Sprite_expl_02;//64*64
SpriteBody Sprite_expl_03;//64*64
SpriteBody Sprite_expl_04;//64*64
SpriteBody Sprite_expl_05;//32*32
SpriteBody Sprite_expl_06;//64*64
SpriteBody Sprite_expl_07;//32*32
SpriteBody Sprite_expl_08;//64*64
SpriteBody Sprite_expl_09;//128*128
SpriteBody Sprite_expl_10;//128*128
SpriteBody Sprite_expl_11;//96*96
//all 128*128
SpriteBody Sprite_expl2_01;
SpriteBody Sprite_expl2_02;
SpriteBody Sprite_expl2_03;
SpriteBody Sprite_expl2_04;
SpriteBody Sprite_expl2_05;
SpriteBody Sprite_expl2_06;
SpriteBody Sprite_expl2_07;
SpriteBody Sprite_expl2_08;
SpriteBody Sprite_expl2_09;
SpriteBody Sprite_expl2_10;
SpriteBody Sprite_expl2_11;


void Bullet::Die(LONGLONG time) {
	die_time = time;
	die_Body.map.SetBeginTime(time);
	status = Triggering;
	double move = main_Body.map.getFrame(TL::pHpte->getIntervals_int()).getheight() / 2;
	Tran.p += {Tran.q.c* move, -Tran.q.s * move};
	if (HitShip != NULL) {
		Tran.q = HitShip->Tran.q;
		velocity = HitShip->velocity;
	}
	UpdateMoTran();
}
void Factory::LoadSprite(){
	std::vector<std::thread>threads;
	threads.push_back( std::thread([]() {
		Vec2D VecShapeDate[16];
		Vec2D vec_err = { -7, -16 };
		Vec2D VecFireShapeData_3[3] = { {0,0},{14,0},{7,30} };
		for (int i = 0; i < 3; ++i)VecFireShapeData_3[i] += vec_err;

		//load Sprite_fire
		Sprite_fire_1.map.push_back_img(fire[16]);
		Sprite_fire_1.map.push_back_img(fire[17]);
		Sprite_fire_1.map.SetIFS(TL::pHpte->PrecFrequency() / 8);
		Sprite_fire_1.tran.p = vec_err;
		Sprite_fire_1.SpriteShape.Set(VecFireShapeData_3, 3);

		Sprite_fire_2.map.push_back_img(fire[14]);
		Sprite_fire_2.map.push_back_img(fire[15]);
		Sprite_fire_2.map.SetIFS(TL::pHpte->PrecFrequency() / 8);
		Sprite_fire_2.tran.p = vec_err;
		Sprite_fire_2.SpriteShape.Set(VecFireShapeData_3, 3);

		Sprite_fire_3.map.push_back_img(fire[12]);
		Sprite_fire_3.map.push_back_img(fire[13]);
		Sprite_fire_3.map.SetIFS(TL::pHpte->PrecFrequency() / 8);
		Sprite_fire_3.tran.p = vec_err;
		Sprite_fire_3.SpriteShape.Set(VecFireShapeData_3, 3);

		VecFireShapeData_3[0] = { 7,0 };
		VecFireShapeData_3[0] = { 0,30 };
		VecFireShapeData_3[0] = { 14,30 };
		for (int i = 0; i < 3; ++i)VecFireShapeData_3[i] += vec_err;

		Sprite_fire_4.map.push_back_img(fire[6]);
		Sprite_fire_4.map.push_back_img(fire[7]);
		Sprite_fire_4.map.SetIFS(TL::pHpte->PrecFrequency() / 8);
		Sprite_fire_4.tran.p = vec_err;
		Sprite_fire_4.SpriteShape.Set(VecFireShapeData_3, 3);

		Sprite_fire_5.map.push_back_img(fire[4]);
		Sprite_fire_5.map.push_back_img(fire[5]);
		Sprite_fire_5.map.SetIFS(TL::pHpte->PrecFrequency() / 8);
		Sprite_fire_5.tran.p = vec_err;
		Sprite_fire_5.SpriteShape.Set(VecFireShapeData_3, 3);

		Sprite_fire_6.map.push_back_img(fire[2]);
		Sprite_fire_6.map.push_back_img(fire[3]);
		Sprite_fire_6.map.SetIFS(TL::pHpte->PrecFrequency() / 8);
		Sprite_fire_6.tran.p = vec_err;
		Sprite_fire_6.SpriteShape.Set(VecFireShapeData_3, 3);






		vec_err = { -(double)playerShip1_blue.getwidth() / 2,-(double)playerShip1_blue.getheight() / 2 };
		Vec2D VecShipShapeData[6] = { {49,0},{97,31},{95,61},{49,74},{3,61},{0,31} };
		for (int i = 0; i < 6; ++i)VecShipShapeData[i] += vec_err;


		Sprite_Ship1_blue.map.push_back_img(playerShip1_blue);
		Sprite_Ship1_blue.tran.p = vec_err;
		Sprite_Ship1_blue.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship1_green.map.push_back_img(playerShip1_green);
		Sprite_Ship1_green.tran.p = vec_err;
		Sprite_Ship1_green.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship1_orange.map.push_back_img(playerShip1_orange);
		Sprite_Ship1_orange.tran.p = vec_err;
		Sprite_Ship1_orange.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship1_red.map.push_back_img(playerShip1_red);
		Sprite_Ship1_red.tran.p = vec_err;
		Sprite_Ship1_red.SpriteShape.Set(VecShipShapeData, 6);
		// 战损
		Sprite_Ship1_damage1.map.push_back_img(playerShip1_damage1);
		Sprite_Ship1_damage1.tran.p = vec_err;
		Sprite_Ship1_damage1.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship1_damage2.map.push_back_img(playerShip1_damage2);
		Sprite_Ship1_damage2.tran.p = vec_err;
		Sprite_Ship1_damage2.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship1_damage3.map.push_back_img(playerShip1_damage3);
		Sprite_Ship1_damage3.tran.p = vec_err - Vec2D(1, 0);
		Sprite_Ship1_damage3.SpriteShape.Set(VecShipShapeData, 6);

		vec_err = { -(double)playerShip2_blue.getwidth() / 2,-(double)playerShip2_blue.getheight() / 2 };
		Vec2D VecShipShapeData_7[7];
		VecShipShapeData_7[0] = { 55,0 };
		VecShipShapeData_7[1] = { 0,43 };
		VecShipShapeData_7[2] = { 18,71 };
		VecShipShapeData_7[3] = { 43,74 };
		VecShipShapeData_7[4] = { 67,74 };
		VecShipShapeData_7[5] = { 93,71 };
		VecShipShapeData_7[6] = { 111,43 };
		for (int i = 0; i < 7; ++i)VecShipShapeData_7[i] += vec_err;

		Sprite_Ship2_blue.map.push_back_img(playerShip2_blue);
		Sprite_Ship2_blue.tran.p = vec_err;
		Sprite_Ship2_blue.SpriteShape.Set(VecShipShapeData_7, 7);

		Sprite_Ship2_green.map.push_back_img(playerShip2_green);
		Sprite_Ship2_green.tran.p = vec_err;
		Sprite_Ship2_green.SpriteShape.Set(VecShipShapeData_7, 7);

		Sprite_Ship2_orange.map.push_back_img(playerShip2_orange);
		Sprite_Ship2_orange.tran.p = vec_err;
		Sprite_Ship2_orange.SpriteShape.Set(VecShipShapeData_7, 7);

		Sprite_Ship2_red.map.push_back_img(playerShip2_red);
		Sprite_Ship2_red.tran.p = vec_err;
		Sprite_Ship2_red.SpriteShape.Set(VecShipShapeData_7, 7);
		// 战损
		Sprite_Ship2_damage1.map.push_back_img(playerShip2_damage1);
		Sprite_Ship2_damage1.tran.p = vec_err;
		Sprite_Ship2_damage1.SpriteShape.Set(VecShipShapeData_7, 7);

		Sprite_Ship2_damage2.map.push_back_img(playerShip2_damage2);
		Sprite_Ship2_damage2.tran.p = vec_err;
		Sprite_Ship2_damage2.SpriteShape.Set(VecShipShapeData_7, 7);

		Sprite_Ship2_damage3.map.push_back_img(playerShip2_damage3);
		Sprite_Ship2_damage3.tran.p = vec_err;
		Sprite_Ship2_damage3.SpriteShape.Set(VecShipShapeData_7, 7);

		vec_err = { -(double)playerShip3_blue.getwidth() / 2,-(double)playerShip3_blue.getheight() / 2 };
		VecShipShapeData[0] = { 45,0 };
		VecShipShapeData[1] = { 0,64 };
		VecShipShapeData[2] = { 35,74 };
		VecShipShapeData[3] = { 61,74 };
		VecShipShapeData[4] = { 97,64 };
		VecShipShapeData[5] = { 52,0 };
		for (int i = 0; i < 6; ++i)VecShipShapeData[i] += vec_err;
		Sprite_Ship3_blue.map.push_back_img(playerShip3_blue);
		Sprite_Ship3_blue.tran.p = vec_err;
		Sprite_Ship3_blue.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship3_green.map.push_back_img(playerShip3_green);
		Sprite_Ship3_green.tran.p = vec_err;
		Sprite_Ship3_green.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship3_orange.map.push_back_img(playerShip3_orange);
		Sprite_Ship3_orange.tran.p = vec_err;
		Sprite_Ship3_orange.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship3_red.map.push_back_img(playerShip3_red);
		Sprite_Ship3_red.tran.p = vec_err;
		Sprite_Ship3_red.SpriteShape.Set(VecShipShapeData, 6);
		// 战损
		Sprite_Ship3_damage1.map.push_back_img(playerShip3_damage1);
		Sprite_Ship3_damage1.tran.p = vec_err;
		Sprite_Ship3_damage1.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship3_damage2.map.push_back_img(playerShip3_damage2);
		Sprite_Ship3_damage2.tran.p = vec_err;
		Sprite_Ship3_damage2.SpriteShape.Set(VecShipShapeData, 6);

		Sprite_Ship3_damage3.map.push_back_img(playerShip3_damage3);
		Sprite_Ship3_damage3.tran.p = vec_err;
		Sprite_Ship3_damage3.SpriteShape.Set(VecShipShapeData, 6);


		vec_err = { -(double)ufoBlue.getwidth() / 2,-(double)ufoBlue.getheight() / 2 };
		Vec2D VecShipShapeData_8[8];
		VecShipShapeData_8[0] = { 45,0 };
		VecShipShapeData_8[1] = { 11,12 };
		VecShipShapeData_8[2] = { 0,45 };
		VecShipShapeData_8[3] = { 11,78 };
		VecShipShapeData_8[4] = { 45,90 };
		VecShipShapeData_8[5] = { 79,78 };
		VecShipShapeData_8[6] = { 78,11 };
		VecShipShapeData_8[7] = { 79,78 };
		for (int i = 0; i < 8; ++i)VecShipShapeData_8[i] += vec_err;
		Sprite_ufoBlue.map.push_back_img(ufoBlue);
		Sprite_ufoBlue.tran.p = vec_err;
		Sprite_ufoBlue.SpriteShape.Set(VecShipShapeData_8, 8);

		Sprite_ufoGreen.map.push_back_img(ufoGreen);
		Sprite_ufoGreen.tran.p = vec_err;
		Sprite_ufoGreen.SpriteShape.Set(VecShipShapeData_8, 8);

		Sprite_ufoYellow.map.push_back_img(ufoYellow);
		Sprite_ufoYellow.tran.p = vec_err;
		Sprite_ufoYellow.SpriteShape.Set(VecShipShapeData_8, 8);

		Sprite_ufoRed.map.push_back_img(ufoRed);
		Sprite_ufoRed.tran.p = vec_err;
		Sprite_ufoRed.SpriteShape.Set(VecShipShapeData_8, 8);


		vec_err = { -(double)shield[0].getwidth() / 2,-(double)shield[0].getheight() / 2 };
		Vec2D VecShipShapeData_10[10];
		VecShipShapeData_10[0] = { 67,0 };
		VecShipShapeData_10[1] = { 26,12 };
		VecShipShapeData_10[2] = { 0,56 };
		VecShipShapeData_10[3] = { 0,79 };
		VecShipShapeData_10[4] = { 12,107 };
		VecShipShapeData_10[5] = { 67,120 };
		VecShipShapeData_10[6] = { 119,107 };
		VecShipShapeData_10[7] = { 132,79 };
		VecShipShapeData_10[8] = { 132,56 };
		VecShipShapeData_10[9] = { 106,12 };
		for (int i = 0; i < 10; ++i)VecShipShapeData_10[i] += vec_err;
		Sprite_shield_1.map.push_back_img(shield[0]);
		Sprite_shield_1.site = Vec2D(0, -15);
		Sprite_shield_1.tran.p = vec_err;
		Sprite_shield_1.SpriteShape.Set(VecShipShapeData_10, 10);

		vec_err = { -(double)shield[1].getwidth() / 2,-(double)shield[1].getheight() / 2 };
		VecShipShapeData_10[0] = { 71,0 };
		VecShipShapeData_10[1] = { 23,16 };
		VecShipShapeData_10[2] = { 0,60 };
		VecShipShapeData_10[3] = { 0,83 };
		VecShipShapeData_10[4] = { 18,118 };
		VecShipShapeData_10[5] = { 71,124 };
		VecShipShapeData_10[6] = { 125,118 };
		VecShipShapeData_10[7] = { 142,83 };
		VecShipShapeData_10[8] = { 142,60 };
		VecShipShapeData_10[9] = { 118,16 };
		for (int i = 0; i < 10; ++i)VecShipShapeData_10[i] += vec_err;
		Sprite_shield_2.map.push_back_img(shield[1]);
		Sprite_shield_2.site = Vec2D(0, -10);
		Sprite_shield_2.tran.p = vec_err;
		Sprite_shield_2.SpriteShape.Set(VecShipShapeData_10, 10);

		vec_err = { -(double)shield[2].getwidth() / 2,-(double)shield[2].getheight() / 2 };
		VecShipShapeData_10[0] = { 72,0 };
		VecShipShapeData_10[1] = { 23,16 };
		VecShipShapeData_10[2] = { 0,60 };
		VecShipShapeData_10[3] = { 0,83 };
		VecShipShapeData_10[4] = { 18,118 };
		VecShipShapeData_10[5] = { 72,136 };
		VecShipShapeData_10[6] = { 125,118 };
		VecShipShapeData_10[7] = { 144,83 };
		VecShipShapeData_10[8] = { 144,60 };
		VecShipShapeData_10[9] = { 118,16 };
		for (int i = 0; i < 10; ++i)VecShipShapeData_10[i] += vec_err;
		Sprite_shield_3.map.push_back_img(shield[2]);
		Sprite_shield_3.tran.p = vec_err;
		Sprite_shield_3.SpriteShape.Set(VecShipShapeData_10, 10);




		vec_err = { -(double)laserBlue01.getwidth() / 2,-(double)laserBlue01.getheight() / 2 };
		VecShapeDate[0] = { 0,0 };
		VecShapeDate[1] = { 0,8 };
		VecShapeDate[2] = { 8,53 };
		VecShapeDate[3] = { 0,53 };

		for (int i = 0; i < 4; ++i)VecShapeDate[i] += vec_err;
		Sprite_laserBlue01.map.push_back_img(laserBlue01);
		Sprite_laserBlue01.tran.p = vec_err;
		Sprite_laserBlue01.SpriteShape.Set(VecShapeDate, 4);





		vec_err = { -(double)laserBlue08.getwidth() / 2,-(double)laserBlue08.getheight() / 2 };
		VecShapeDate[0] = { 24,0 };
		VecShapeDate[1] = { 0,22 };
		VecShapeDate[2] = { 23,45 };
		VecShapeDate[3] = { 47,23 };

		for (int i = 0; i < 4; ++i)VecShapeDate[i] += vec_err;
		Sprite_laserflareBlue01.map.push_back_img(laserBlue08);
		Sprite_laserflareBlue01.map.push_back_img(laserBlue09);
		Sprite_laserflareBlue01.map.SetIFS(TL::pHpte->PrecFrequency() / 4);
		Sprite_laserflareBlue01.map.isOnce = true;
		Sprite_laserflareBlue01.tran.p = vec_err;
		Sprite_laserflareBlue01.SpriteShape.Set(VecShapeDate, 4);


		//Sprite_Enemies

		//Enemies
		/*IMAGE Sprite_enemyBlack1;
		IMAGE Sprite_enemyBlack2;
		IMAGE Sprite_enemyBlack3;
		IMAGE Sprite_enemyBlack4;
		IMAGE Sprite_enemyBlack5;

		IMAGE Sprite_enemyBlue1;
		IMAGE Sprite_enemyBlue2;
		IMAGE Sprite_enemyBlue3;
		IMAGE Sprite_enemyBlue4;
		IMAGE Sprite_enemyBlue5;

		IMAGE Sprite_enemyGreen1;
		IMAGE Sprite_enemyGreen2;
		IMAGE Sprite_enemyGreen3;
		IMAGE Sprite_enemyGreen4;
		IMAGE Sprite_enemyGreen5;

		IMAGE Sprite_enemyRed1;
		IMAGE Sprite_enemyRed2;
		IMAGE Sprite_enemyRed3;
		IMAGE Sprite_enemyRed4;
		IMAGE Sprite_enemyRed5;*/

		vec_err = { -(double)enemyBlack1.getwidth() / 2,-(double)enemyBlack1.getheight() / 2 };
		VecShapeDate[0] = { 16,1 };
		VecShapeDate[1] = { 0,25 };
		VecShapeDate[2] = { 22,83 };
		VecShapeDate[3] = { 70,83 };
		VecShapeDate[4] = { 92,26 };
		VecShapeDate[5] = { 75,1 };
		for (int i = 0; i < 6; ++i)VecShapeDate[i] += vec_err;

		Sprite_enemyBlack1.map.push_back_img(enemyBlack1);
		Sprite_enemyBlack1.tran.p = vec_err;
		Sprite_enemyBlack1.SpriteShape.Set(VecShapeDate, 6);

		Sprite_enemyBlue1.map.push_back_img(enemyBlue1);
		Sprite_enemyBlue1.tran.p = vec_err;
		Sprite_enemyBlue1.SpriteShape.Set(VecShapeDate, 6);

		Sprite_enemyGreen1.map.push_back_img(enemyGreen1);
		Sprite_enemyGreen1.tran.p = vec_err;
		Sprite_enemyGreen1.SpriteShape.Set(VecShapeDate, 6);

		Sprite_enemyRed1.map.push_back_img(enemyRed1);
		Sprite_enemyRed1.tran.p = vec_err;
		Sprite_enemyRed1.SpriteShape.Set(VecShapeDate, 6);

		vec_err = { -(double)enemyBlack2.getwidth() / 2,-(double)enemyBlack2.getheight() / 2 };
		VecShapeDate[0] = { 52,0 };
		VecShapeDate[1] = { 0,26 };
		VecShapeDate[2] = { 28,83 };
		VecShapeDate[3] = { 75,83 };
		VecShapeDate[4] = { 103,26 };
		for (int i = 0; i < 5; ++i)VecShapeDate[i] += vec_err;

		Sprite_enemyBlack2.map.push_back_img(enemyBlack2);
		Sprite_enemyBlack2.tran.p = vec_err;
		Sprite_enemyBlack2.SpriteShape.Set(VecShapeDate, 5);

		Sprite_enemyBlue2.map.push_back_img(enemyBlue2);
		Sprite_enemyBlue2.tran.p = vec_err;
		Sprite_enemyBlue2.SpriteShape.Set(VecShapeDate, 5);

		Sprite_enemyGreen2.map.push_back_img(enemyGreen2);
		Sprite_enemyGreen2.tran.p = vec_err;
		Sprite_enemyGreen2.SpriteShape.Set(VecShapeDate, 5);

		Sprite_enemyRed2.map.push_back_img(enemyRed2);
		Sprite_enemyRed2.tran.p = vec_err;
		Sprite_enemyRed2.SpriteShape.Set(VecShapeDate, 5);


		vec_err = { -(double)enemyBlack3.getwidth() / 2,-(double)enemyBlack3.getheight() / 2 };
		VecShapeDate[0] = { 43,1 };
		VecShapeDate[1] = { 0,38 };
		VecShapeDate[2] = { 13,83 };
		VecShapeDate[3] = { 88,83 };
		VecShapeDate[4] = { 101,38 };
		for (int i = 0; i < 5; ++i)VecShapeDate[i] += vec_err;

		Sprite_enemyBlack3.map.push_back_img(enemyBlack3);
		Sprite_enemyBlack3.tran.p = vec_err;
		Sprite_enemyBlack3.SpriteShape.Set(VecShapeDate, 5);

		Sprite_enemyBlue3.map.push_back_img(enemyBlue3);
		Sprite_enemyBlue3.tran.p = vec_err;
		Sprite_enemyBlue3.SpriteShape.Set(VecShapeDate, 5);

		Sprite_enemyGreen3.map.push_back_img(enemyGreen3);
		Sprite_enemyGreen3.tran.p = vec_err;
		Sprite_enemyGreen3.SpriteShape.Set(VecShapeDate, 5);

		Sprite_enemyRed3.map.push_back_img(enemyRed3);
		Sprite_enemyRed3.tran.p = vec_err;
		Sprite_enemyRed3.SpriteShape.Set(VecShapeDate, 5);

		vec_err = { -(double)enemyBlack4.getwidth() / 2,-(double)enemyBlack4.getheight() / 2 };
		VecShapeDate[0] = { 23,0 };
		VecShapeDate[1] = { 1,13 };
		VecShapeDate[2] = { 1,61 };
		VecShapeDate[3] = { 30,83 };
		VecShapeDate[4] = { 51,83 };
		VecShapeDate[5] = { 80,61 };
		VecShapeDate[6] = { 80,13 };
		for (int i = 0; i < 7; ++i)VecShapeDate[i] += vec_err;

		Sprite_enemyBlack4.map.push_back_img(enemyBlack4);
		Sprite_enemyBlack4.tran.p = vec_err;
		Sprite_enemyBlack4.SpriteShape.Set(VecShapeDate, 7);

		Sprite_enemyBlue4.map.push_back_img(enemyBlue4);
		Sprite_enemyBlue4.tran.p = vec_err;
		Sprite_enemyBlue4.SpriteShape.Set(VecShapeDate, 7);

		Sprite_enemyGreen4.map.push_back_img(enemyGreen4);
		Sprite_enemyGreen4.tran.p = vec_err;
		Sprite_enemyGreen4.SpriteShape.Set(VecShapeDate, 7);

		Sprite_enemyRed4.map.push_back_img(enemyRed4);
		Sprite_enemyRed4.tran.p = vec_err;
		Sprite_enemyRed4.SpriteShape.Set(VecShapeDate, 7);

		vec_err = { -(double)enemyBlack5.getwidth() / 2,-(double)enemyBlack5.getheight() / 2 };
		VecShapeDate[0] = { 1,1 };
		VecShapeDate[1] = { 21,73 };
		VecShapeDate[2] = { 37,83 };
		VecShapeDate[3] = { 58,83 };
		VecShapeDate[4] = { 75,73 };
		VecShapeDate[5] = { 95,1 };
		for (int i = 0; i < 6; ++i)VecShapeDate[i] += vec_err;

		Sprite_enemyBlack5.map.push_back_img(enemyBlack5);
		Sprite_enemyBlack5.tran.p = vec_err;
		Sprite_enemyBlack5.SpriteShape.Set(VecShapeDate, 6);

		Sprite_enemyBlue5.map.push_back_img(enemyBlue5);
		Sprite_enemyBlue5.tran.p = vec_err;
		Sprite_enemyBlue5.SpriteShape.Set(VecShapeDate, 6);

		Sprite_enemyGreen5.map.push_back_img(enemyGreen5);
		Sprite_enemyGreen5.tran.p = vec_err;
		Sprite_enemyGreen5.SpriteShape.Set(VecShapeDate, 6);

		Sprite_enemyRed5.map.push_back_img(enemyRed5);
		Sprite_enemyRed5.tran.p = vec_err;
		Sprite_enemyRed5.SpriteShape.Set(VecShapeDate, 6);
		}));
	

	////Explosion
	threads.push_back( std::thread([]() {
		Vec2D vec_err = { -(double)expl_01[0].getwidth() / 2,-(double)expl_01[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl_01.map.push_back_img(expl_01[i]);
		Sprite_expl_01.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl_01.map.isOnce = true;
		Sprite_expl_01.tran.p = vec_err;

		vec_err = { -(double)expl_02[0].getwidth() / 2,-(double)expl_02[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl_02.map.push_back_img(expl_02[i]);
		Sprite_expl_02.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl_02.map.isOnce = true;
		Sprite_expl_02.tran.p = vec_err;

		vec_err = { -(double)expl_03[0].getwidth() / 2,-(double)expl_03[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl_03.map.push_back_img(expl_03[i]);
		Sprite_expl_03.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl_03.map.isOnce = true;
		Sprite_expl_03.tran.p = vec_err;

		vec_err = { -(double)expl_04[0].getwidth() / 2,-(double)expl_04[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl_04.map.push_back_img(expl_04[i]);
		Sprite_expl_04.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl_04.map.isOnce = true;
		Sprite_expl_04.tran.p = vec_err;

		vec_err = { -(double)expl_05[0].getwidth() / 2,-(double)expl_05[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl_05.map.push_back_img(expl_05[i]);
		Sprite_expl_05.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl_05.map.isOnce = true;
		Sprite_expl_05.tran.p = vec_err;

		vec_err = { -(double)expl_06[0].getwidth() / 2,-(double)expl_06[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl_06.map.push_back_img(expl_06[i]);
		Sprite_expl_06.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl_06.map.isOnce = true;
		Sprite_expl_06.tran.p = vec_err;

		vec_err = { -(double)expl_07[0].getwidth() / 2,-(double)expl_07[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl_07.map.push_back_img(expl_07[i]);
		Sprite_expl_07.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl_07.map.isOnce = true;
		Sprite_expl_07.tran.p = vec_err;

		vec_err = { -(double)expl_08[0].getwidth() / 2,-(double)expl_08[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl_08.map.push_back_img(expl_08[i]);
		Sprite_expl_08.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl_08.map.isOnce = true;
		Sprite_expl_08.tran.p = vec_err;

		vec_err = { -(double)expl_09[0].getwidth() / 2,-(double)expl_09[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl_09.map.push_back_img(expl_09[i]);
		Sprite_expl_09.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl_09.map.isOnce = true;
		Sprite_expl_09.tran.p = vec_err;

		vec_err = { -(double)expl_10[0].getwidth() / 2,-(double)expl_10[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl_10.map.push_back_img(expl_10[i]);
		Sprite_expl_10.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl_10.map.isOnce = true;
		Sprite_expl_10.tran.p = vec_err;

		vec_err = { -(double)expl_11[0].getwidth() / 2,-(double)expl_11[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl_11.map.push_back_img(expl_11[i]);
		Sprite_expl_11.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl_11.map.isOnce = true;
		Sprite_expl_11.tran.p = vec_err;
		}));
	


	threads.push_back(std::thread([]() {
		Vec2D vec_err = { -(double)expl2_01[0].getwidth() / 2,-(double)expl2_01[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl2_01.map.push_back_img(expl2_01[i]);
		Sprite_expl2_01.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl2_01.map.isOnce = true;
		Sprite_expl2_01.tran.p = vec_err;

		vec_err = { -(double)expl2_02[0].getwidth() / 2,-(double)expl2_02[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl2_02.map.push_back_img(expl2_02[i]);
		Sprite_expl2_02.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl2_02.map.isOnce = true;
		Sprite_expl2_02.tran.p = vec_err;

		vec_err = { -(double)expl2_03[0].getwidth() / 2,-(double)expl2_03[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl2_03.map.push_back_img(expl2_03[i]);
		Sprite_expl2_03.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl2_03.map.isOnce = true;
		Sprite_expl2_03.tran.p = vec_err;

		vec_err = { -(double)expl2_04[0].getwidth() / 2,-(double)expl2_04[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl2_04.map.push_back_img(expl2_04[i]);
		Sprite_expl2_04.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl2_04.map.isOnce = true;
		Sprite_expl2_04.tran.p = vec_err;

		vec_err = { -(double)expl2_05[0].getwidth() / 2,-(double)expl2_05[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl2_05.map.push_back_img(expl2_05[i]);
		Sprite_expl2_05.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl2_05.map.isOnce = true;
		Sprite_expl2_05.tran.p = vec_err;

		vec_err = { -(double)expl2_06[0].getwidth() / 2,-(double)expl2_06[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl2_06.map.push_back_img(expl2_06[i]);
		Sprite_expl2_06.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl2_06.map.isOnce = true;
		Sprite_expl2_06.tran.p = vec_err;

		vec_err = { -(double)expl2_07[0].getwidth() / 2,-(double)expl2_07[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl2_07.map.push_back_img(expl2_07[i]);
		Sprite_expl2_07.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl2_07.map.isOnce = true;
		Sprite_expl2_07.tran.p = vec_err;

		vec_err = { -(double)expl2_08[0].getwidth() / 2,-(double)expl2_08[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl2_08.map.push_back_img(expl2_08[i]);
		Sprite_expl2_08.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl2_08.map.isOnce = true;
		Sprite_expl2_08.tran.p = vec_err;

		vec_err = { -(double)expl2_09[0].getwidth() / 2,-(double)expl2_09[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl2_09.map.push_back_img(expl2_09[i]);
		Sprite_expl2_09.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl2_09.map.isOnce = true;
		Sprite_expl2_09.tran.p = vec_err;

		vec_err = { -(double)expl2_10[0].getwidth() / 2,-(double)expl2_10[0].getheight() / 2 };
		for (int i = 0; i < 32; ++i) Sprite_expl2_10.map.push_back_img(expl2_10[i]);
		Sprite_expl2_10.map.SetIFS(TL::pHpte->PrecFrequency() / 32);
		Sprite_expl2_10.map.isOnce = true;
		Sprite_expl2_10.tran.p = vec_err;

		vec_err = { -(double)expl2_11[0].getwidth() / 2,-(double)expl2_11[0].getheight() / 2 };
		for (int i = 0; i < 24; ++i) Sprite_expl2_11.map.push_back_img(expl2_11[i]);
		Sprite_expl2_11.map.SetIFS(TL::pHpte->PrecFrequency() / 24);
		Sprite_expl2_11.map.isOnce = true;
		Sprite_expl2_11.tran.p = vec_err;
		}));
	for (auto& iter : threads) {
		iter.join();
	}
}