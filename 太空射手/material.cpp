#include "material.h"
#include<iostream>
//！！不要使用自动缩进

//Backgrounds
IMAGE Background_black;
IMAGE Background_blue;
IMAGE Background_darkPurple;
IMAGE Background_purple;

//PLAYER
IMAGE playerShip1_blue;
IMAGE playerShip1_green;
IMAGE playerShip1_orange;
IMAGE playerShip1_red;
IMAGE playerShip2_blue;
IMAGE playerShip2_green;
IMAGE playerShip2_orange;
IMAGE playerShip2_red;
IMAGE playerShip3_blue;
IMAGE playerShip3_green;
IMAGE playerShip3_orange;
IMAGE playerShip3_red;
IMAGE ufoBlue;
IMAGE ufoGreen;
IMAGE ufoRed;
IMAGE ufoYellow;

//Damage
IMAGE playerShip1_damage1;
IMAGE playerShip1_damage2;
IMAGE playerShip1_damage3;
IMAGE playerShip2_damage1;
IMAGE playerShip2_damage2;
IMAGE playerShip2_damage3;
IMAGE playerShip3_damage1;
IMAGE playerShip3_damage2;
IMAGE playerShip3_damage3;

//Effects

IMAGE fire[19];
IMAGE shield[3];
IMAGE speed;
IMAGE star[3];

//Enemies
IMAGE enemyBlack1;
IMAGE enemyBlack2;
IMAGE enemyBlack3;
IMAGE enemyBlack4;
IMAGE enemyBlack5;

IMAGE enemyBlue1;
IMAGE enemyBlue2;
IMAGE enemyBlue3;
IMAGE enemyBlue4;
IMAGE enemyBlue5;

IMAGE enemyGreen1;
IMAGE enemyGreen2;
IMAGE enemyGreen3;
IMAGE enemyGreen4;
IMAGE enemyGreen5;

IMAGE enemyRed1;
IMAGE enemyRed2;
IMAGE enemyRed3;
IMAGE enemyRed4;
IMAGE enemyRed5;

//Lasers
IMAGE laserBlue01;
IMAGE laserBlue02;
IMAGE laserBlue03;
IMAGE laserBlue04;
IMAGE laserBlue05;
IMAGE laserBlue06;
IMAGE laserBlue07;
IMAGE laserBlue08;
IMAGE laserBlue09;
IMAGE laserBlue10;
IMAGE laserBlue11;
IMAGE laserBlue12;
IMAGE laserBlue13;
IMAGE laserBlue14;
IMAGE laserBlue15;
IMAGE laserBlue16;


IMAGE laserGreen01;
IMAGE laserGreen02;
IMAGE laserGreen03;
IMAGE laserGreen04;
IMAGE laserGreen05;
IMAGE laserGreen06;
IMAGE laserGreen07;
IMAGE laserGreen08;
IMAGE laserGreen09;
IMAGE laserGreen10;
IMAGE laserGreen11;
IMAGE laserGreen12;
IMAGE laserGreen13;
IMAGE laserGreen14;
IMAGE laserGreen15;
IMAGE laserGreen16;

IMAGE laserRed01;
IMAGE laserRed02;
IMAGE laserRed03;
IMAGE laserRed04;
IMAGE laserRed05;
IMAGE laserRed06;
IMAGE laserRed07;
IMAGE laserRed08;
IMAGE laserRed09;
IMAGE laserRed10;
IMAGE laserRed11;
IMAGE laserRed12;
IMAGE laserRed13;
IMAGE laserRed14;
IMAGE laserRed15;
IMAGE laserRed16;


IMAGE meteorBrown_big1;
IMAGE meteorBrown_big2;
IMAGE meteorBrown_big3;
IMAGE meteorBrown_big4;
IMAGE meteorBrown_med1;
IMAGE meteorBrown_med3;
IMAGE meteorBrown_small1;
IMAGE meteorBrown_small2;
IMAGE meteorBrown_tiny1;
IMAGE meteorBrown_tiny2;
IMAGE meteorGrey_big1;
IMAGE meteorGrey_big2;
IMAGE meteorGrey_big3;
IMAGE meteorGrey_big4;
IMAGE meteorGrey_med1;
IMAGE meteorGrey_med2;
IMAGE meteorGrey_small1;
IMAGE meteorGrey_small2;
IMAGE meteorGrey_tiny1;
IMAGE meteorGrey_tiny2;


//Power_ups
IMAGE bold_silver;
IMAGE bolt_bronze;
IMAGE bolt_gold;
IMAGE pill_blue;
IMAGE pill_green;
IMAGE pill_red;
IMAGE pill_yellow;
IMAGE powerupBlue;
IMAGE powerupBlue_bolt;
IMAGE powerupBlue_shield;
IMAGE powerupBlue_star;
IMAGE powerupGreen;
IMAGE powerupGreen_bolt;
IMAGE powerupGreen_shield;
IMAGE powerupGreen_star;
IMAGE powerupRed;
IMAGE powerupRed_bolt;
IMAGE powerupRed_shield;
IMAGE powerupRed_star;
IMAGE powerupYellow;
IMAGE powerupYellow_bolt;
IMAGE powerupYellow_shield;
IMAGE powerupYellow_star;
IMAGE shield_bronze;
IMAGE shield_gold;
IMAGE shield_silver;
IMAGE star_bronze;
IMAGE star_gold;
IMAGE star_silver;
IMAGE things_bronze;
IMAGE things_gold;
IMAGE things_silver;

//UI
IMAGE buttonBlue;
IMAGE buttonGreen;
IMAGE buttonRed;
IMAGE buttonYellow;
IMAGE cursor;
IMAGE numeral0;
IMAGE numeral1;
IMAGE numeral2;
IMAGE numeral3;
IMAGE numeral4;
IMAGE numeral5;
IMAGE numeral6;
IMAGE numeral7;
IMAGE numeral8;
IMAGE numeral9;

IMAGE numeralX;
IMAGE playerLife1_blue;
IMAGE playerLife1_green;
IMAGE playerLife1_orange;
IMAGE playerLife1_red;
IMAGE playerLife2_blue;
IMAGE playerLife2_green;
IMAGE playerLife2_orange;
IMAGE playerLife2_red;
IMAGE playerLife3_blue;
IMAGE playerLife3_green;
IMAGE playerLife3_orange;
IMAGE playerLife3_red;


//Explosion
IMAGE expl_01[24];
IMAGE expl_02[24];
IMAGE expl_03[24];
IMAGE expl_04[24];
IMAGE expl_05[24];
IMAGE expl_06[32];
IMAGE expl_07[32];
IMAGE expl_08[32];
IMAGE expl_09[32];
IMAGE expl_10[32];
IMAGE expl_11[24];
IMAGE expl2_01[24];
IMAGE expl2_02[24];
IMAGE expl2_03[24];
IMAGE expl2_04[24];
IMAGE expl2_05[24];
IMAGE expl2_06[32];
IMAGE expl2_07[32];
IMAGE expl2_08[32];
IMAGE expl2_09[32];
IMAGE expl2_10[32];
IMAGE expl2_11[24];
//用于同名字符串文件名和变量名 生成定义const WCHAR* name = "name.type"


#define CTYPE_NMAE_STR_DEF(name,type)const WCHAR* name = COMBINE2_STR(name,.##type)
#define CTYPE_ADDR_NAME_STR_DEF(addr,name,type)const WCHAR* name = COMBINE3_STR(addr,name,.##type)
//WAV
#define WAV_STR(name) CTYPE_ADDR_NAME_STR_DEF(E:/文件夹/WorkSpace/桌面资料库/素材/太空射手套件/Bonus/,name,wav) //const WCHAR* name = COMBINE_STR(name,.wav)

WAV_STR(sfx_laser1);
WAV_STR(sfx_laser2);
WAV_STR(sfx_lose);
WAV_STR(sfx_shieldDown);
WAV_STR(sfx_shieldUp);
WAV_STR(sfx_twoTone);
WAV_STR(sfx_zap);
WAV_STR(sfx_explosion04);

//TTF
#define TTF_STR(name) CTYPE_ADDR_NAME_STR_DEF(E:/文件夹/WorkSpace/桌面资料库/素材/太空射手套件/Bonus/,name,ttf)

TTF_STR(kenvector_future);
TTF_STR(kenvector_future_thin);

void load_material()
{

	


#define COMBINE_FILENAME_MATERIAL_STR(addr,name) NAME_TO_STR(E:/文件夹/WorkSpace/桌面资料库/素材/太空射手套件/addr##name##.png)

	//Backgrounds
#define LOAD_IMAGE_Backgrounds(name) loadimage(&Background_##name,COMBINE_FILENAME_MATERIAL_STR(Backgrounds/,name),0,0,true)
	LOAD_IMAGE_Backgrounds(black);
	LOAD_IMAGE_Backgrounds(blue);
	LOAD_IMAGE_Backgrounds(darkPurple);
	LOAD_IMAGE_Backgrounds(purple);


	//Player
#define LOAD_IMAGE_PLAYER(name) loadimage(&name,COMBINE_FILENAME_MATERIAL_STR(PNG/,name),0,0,true)
	LOAD_IMAGE_PLAYER(playerShip1_blue);
	LOAD_IMAGE_PLAYER(playerShip1_green);
	LOAD_IMAGE_PLAYER(playerShip1_orange);
	LOAD_IMAGE_PLAYER(playerShip1_red);
	LOAD_IMAGE_PLAYER(playerShip2_blue);
	LOAD_IMAGE_PLAYER(playerShip2_green);
	LOAD_IMAGE_PLAYER(playerShip2_orange);
	LOAD_IMAGE_PLAYER(playerShip2_red);
	LOAD_IMAGE_PLAYER(playerShip3_blue);
	LOAD_IMAGE_PLAYER(playerShip3_green);
	LOAD_IMAGE_PLAYER(playerShip3_orange);
	LOAD_IMAGE_PLAYER(playerShip3_red);

	LOAD_IMAGE_PLAYER(ufoBlue);
	LOAD_IMAGE_PLAYER(ufoGreen);
	LOAD_IMAGE_PLAYER(ufoRed);
	LOAD_IMAGE_PLAYER(ufoYellow);

	//Damage
#define LOAD_IMAGE_Damage(name) loadimage(&name,COMBINE_FILENAME_MATERIAL_STR(PNG/Damage/,name),0,0,true)
	LOAD_IMAGE_Damage(playerShip1_damage1);
	LOAD_IMAGE_Damage(playerShip1_damage2);
	LOAD_IMAGE_Damage(playerShip1_damage3);
	LOAD_IMAGE_Damage(playerShip2_damage1);
	LOAD_IMAGE_Damage(playerShip2_damage2);
	LOAD_IMAGE_Damage(playerShip2_damage3);
	LOAD_IMAGE_Damage(playerShip3_damage1);
	LOAD_IMAGE_Damage(playerShip3_damage2);
	LOAD_IMAGE_Damage(playerShip3_damage3);
	//Effects
#define LOAD_IMAGE_Effects(name) loadimage(&name,COMBINE_FILENAME_MATERIAL_STR(PNG/Effects/,name),0,0,true)
	WCHAR wcBuf[500] = {0};
	
	for (int i = 0; i < 19; ++i) {
		
		if(i<10)swprintf_s(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Effects/fire0, %d), i);
		else swprintf_s(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Effects/fire, %d), i);
		loadimage(&fire[i], wcBuf, 0, 0, true);
	}
	for (int i = 0; i < 3; ++i) {

		wsprintf(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Effects/shield, %d), i+1);
		loadimage(&shield[i], wcBuf, 0, 0, true);
	}
	LOAD_IMAGE_Effects(speed);
	for (int i = 0; i < 3; ++i) {

		wsprintf(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Effects/star, %d), i+1);
		loadimage(&star[i], wcBuf, 0, 0, true);
	}

	//Enemies
#define LOAD_IMAGE_Enemies(name) loadimage(&name,COMBINE_FILENAME_MATERIAL_STR(PNG/Enemies/,name),0,0,true)

	LOAD_IMAGE_Enemies(enemyBlack1);
	LOAD_IMAGE_Enemies(enemyBlack2);
	LOAD_IMAGE_Enemies(enemyBlack3);
	LOAD_IMAGE_Enemies(enemyBlack4);
	LOAD_IMAGE_Enemies(enemyBlack5);

	LOAD_IMAGE_Enemies(enemyBlue1);
	LOAD_IMAGE_Enemies(enemyBlue2);
	LOAD_IMAGE_Enemies(enemyBlue3);
	LOAD_IMAGE_Enemies(enemyBlue4);
	LOAD_IMAGE_Enemies(enemyBlue5);

	LOAD_IMAGE_Enemies(enemyGreen1);
	LOAD_IMAGE_Enemies(enemyGreen2);
	LOAD_IMAGE_Enemies(enemyGreen3);
	LOAD_IMAGE_Enemies(enemyGreen4);
	LOAD_IMAGE_Enemies(enemyGreen5);

	LOAD_IMAGE_Enemies(enemyRed1);
	LOAD_IMAGE_Enemies(enemyRed2);
	LOAD_IMAGE_Enemies(enemyRed3);
	LOAD_IMAGE_Enemies(enemyRed4);
	LOAD_IMAGE_Enemies(enemyRed5);

	//Lasers
#define LOAD_IMAGE_Lasers(name) loadimage(&name,COMBINE_FILENAME_MATERIAL_STR(PNG/Lasers/,name),0,0,true)

	LOAD_IMAGE_Lasers(laserBlue01);
	LOAD_IMAGE_Lasers(laserBlue02);
	LOAD_IMAGE_Lasers(laserBlue03);
	LOAD_IMAGE_Lasers(laserBlue04);
	LOAD_IMAGE_Lasers(laserBlue05);
	LOAD_IMAGE_Lasers(laserBlue06);
	LOAD_IMAGE_Lasers(laserBlue07);
	LOAD_IMAGE_Lasers(laserBlue08);
	LOAD_IMAGE_Lasers(laserBlue09);
	LOAD_IMAGE_Lasers(laserBlue10);
	LOAD_IMAGE_Lasers(laserBlue11);
	LOAD_IMAGE_Lasers(laserBlue12);
	LOAD_IMAGE_Lasers(laserBlue13);
	LOAD_IMAGE_Lasers(laserBlue14);
	LOAD_IMAGE_Lasers(laserBlue15);
	LOAD_IMAGE_Lasers(laserBlue16);


	LOAD_IMAGE_Lasers(laserGreen01);
	LOAD_IMAGE_Lasers(laserGreen02);
	LOAD_IMAGE_Lasers(laserGreen03);
	LOAD_IMAGE_Lasers(laserGreen04);
	LOAD_IMAGE_Lasers(laserGreen05);
	LOAD_IMAGE_Lasers(laserGreen06);
	LOAD_IMAGE_Lasers(laserGreen07);
	LOAD_IMAGE_Lasers(laserGreen08);
	LOAD_IMAGE_Lasers(laserGreen09);
	LOAD_IMAGE_Lasers(laserGreen10);
	LOAD_IMAGE_Lasers(laserGreen11);
	LOAD_IMAGE_Lasers(laserGreen12);
	LOAD_IMAGE_Lasers(laserGreen13);
	LOAD_IMAGE_Lasers(laserGreen14);
	LOAD_IMAGE_Lasers(laserGreen15);
	LOAD_IMAGE_Lasers(laserGreen16);

	LOAD_IMAGE_Lasers(laserRed01);
	LOAD_IMAGE_Lasers(laserRed02);
	LOAD_IMAGE_Lasers(laserRed03);
	LOAD_IMAGE_Lasers(laserRed04);
	LOAD_IMAGE_Lasers(laserRed05);
	LOAD_IMAGE_Lasers(laserRed06);
	LOAD_IMAGE_Lasers(laserRed07);
	LOAD_IMAGE_Lasers(laserRed08);
	LOAD_IMAGE_Lasers(laserRed09);
	LOAD_IMAGE_Lasers(laserRed10);
	LOAD_IMAGE_Lasers(laserRed11);
	LOAD_IMAGE_Lasers(laserRed12);
	LOAD_IMAGE_Lasers(laserRed13);
	LOAD_IMAGE_Lasers(laserRed14);
	LOAD_IMAGE_Lasers(laserRed15);
	LOAD_IMAGE_Lasers(laserRed16);


	LOAD_IMAGE_Lasers(meteorBrown_big1);
	LOAD_IMAGE_Lasers(meteorBrown_big2);
	LOAD_IMAGE_Lasers(meteorBrown_big3);
	LOAD_IMAGE_Lasers(meteorBrown_big4);
	LOAD_IMAGE_Lasers(meteorBrown_med1);
	LOAD_IMAGE_Lasers(meteorBrown_med3);
	LOAD_IMAGE_Lasers(meteorBrown_small1);
	LOAD_IMAGE_Lasers(meteorBrown_small2);
	LOAD_IMAGE_Lasers(meteorBrown_tiny1);
	LOAD_IMAGE_Lasers(meteorBrown_tiny2);
	LOAD_IMAGE_Lasers(meteorGrey_big1);
	LOAD_IMAGE_Lasers(meteorGrey_big2);
	LOAD_IMAGE_Lasers(meteorGrey_big3);
	LOAD_IMAGE_Lasers(meteorGrey_big4);
	LOAD_IMAGE_Lasers(meteorGrey_med1);
	LOAD_IMAGE_Lasers(meteorGrey_med2);
	LOAD_IMAGE_Lasers(meteorGrey_small1);
	LOAD_IMAGE_Lasers(meteorGrey_small2);
	LOAD_IMAGE_Lasers(meteorGrey_tiny1);
	LOAD_IMAGE_Lasers(meteorGrey_tiny2);

	//Power_ups
#define LOAD_IMAGE_Power_ups(name) loadimage(&name,COMBINE_FILENAME_MATERIAL_STR(PNG/Power-ups/,name),0,0,true)

	LOAD_IMAGE_Power_ups(bold_silver);
	LOAD_IMAGE_Power_ups(bolt_bronze);
	LOAD_IMAGE_Power_ups(bolt_gold);
	LOAD_IMAGE_Power_ups(pill_blue);
	LOAD_IMAGE_Power_ups(pill_green);
	LOAD_IMAGE_Power_ups(pill_red);
	LOAD_IMAGE_Power_ups(pill_yellow);
	LOAD_IMAGE_Power_ups(powerupBlue);
	LOAD_IMAGE_Power_ups(powerupBlue_bolt);
	LOAD_IMAGE_Power_ups(powerupBlue_shield);
	LOAD_IMAGE_Power_ups(powerupBlue_star);
	LOAD_IMAGE_Power_ups(powerupGreen);
	LOAD_IMAGE_Power_ups(powerupGreen_bolt);
	LOAD_IMAGE_Power_ups(powerupGreen_shield);
	LOAD_IMAGE_Power_ups(powerupGreen_star);
	LOAD_IMAGE_Power_ups(powerupRed);
	LOAD_IMAGE_Power_ups(powerupRed_bolt);
	LOAD_IMAGE_Power_ups(powerupRed_shield);
	LOAD_IMAGE_Power_ups(powerupRed_star);
	LOAD_IMAGE_Power_ups(powerupYellow);
	LOAD_IMAGE_Power_ups(powerupYellow_bolt);
	LOAD_IMAGE_Power_ups(powerupYellow_shield);
	LOAD_IMAGE_Power_ups(powerupYellow_star);
	LOAD_IMAGE_Power_ups(shield_bronze);
	LOAD_IMAGE_Power_ups(shield_gold);
	LOAD_IMAGE_Power_ups(shield_silver);
	LOAD_IMAGE_Power_ups(star_bronze);
	LOAD_IMAGE_Power_ups(star_gold);
	LOAD_IMAGE_Power_ups(star_silver);
	LOAD_IMAGE_Power_ups(things_bronze);
	LOAD_IMAGE_Power_ups(things_gold);
	LOAD_IMAGE_Power_ups(things_silver);

	//UI
#define LOAD_IMAGE_UI(name) loadimage(&name,COMBINE_FILENAME_MATERIAL_STR(PNG/UI/,name),0,0,true)

	LOAD_IMAGE_UI(buttonBlue);
	LOAD_IMAGE_UI(buttonGreen);
	LOAD_IMAGE_UI(buttonRed);
	LOAD_IMAGE_UI(buttonYellow);
	LOAD_IMAGE_UI(cursor);
	LOAD_IMAGE_UI(numeral0);
	LOAD_IMAGE_UI(numeral1);
	LOAD_IMAGE_UI(numeral2);
	LOAD_IMAGE_UI(numeral3);
	LOAD_IMAGE_UI(numeral4);
	LOAD_IMAGE_UI(numeral5);
	LOAD_IMAGE_UI(numeral6);
	LOAD_IMAGE_UI(numeral7);
	LOAD_IMAGE_UI(numeral8);
	LOAD_IMAGE_UI(numeral9);

	LOAD_IMAGE_UI(numeralX);
	LOAD_IMAGE_UI(playerLife1_blue);
	LOAD_IMAGE_UI(playerLife1_green);
	LOAD_IMAGE_UI(playerLife1_orange);
	LOAD_IMAGE_UI(playerLife1_red);
	LOAD_IMAGE_UI(playerLife2_blue);
	LOAD_IMAGE_UI(playerLife2_green);
	LOAD_IMAGE_UI(playerLife2_orange);
	LOAD_IMAGE_UI(playerLife2_red);
	LOAD_IMAGE_UI(playerLife3_blue);
	LOAD_IMAGE_UI(playerLife3_green);
	LOAD_IMAGE_UI(playerLife3_orange);
	LOAD_IMAGE_UI(playerLife3_red);

	//Effects
//#define LOAD_IMAGE_Explosion(name) loadimage(&name,COMBINE_FILENAME_MATERIAL_STR(PNG/Explosion/,name),0,0,true)
	
	
	IMAGE* pexpl_[] = { expl_01,expl_02,expl_03,expl_04,expl_05,expl_06,expl_07,expl_08,expl_09,expl_10,expl_11 };
	for(int j = 0; j < 11; ++j)
		if (j == 0) for (int i = 0; i < 24; ++i, ++pexpl_[j]) {
			swprintf_s(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Explosion/expl_%02d_00,%02d), j + 1, i);
			loadimage(pexpl_[j], wcBuf, 0, 0, true);
		}
		else if(j<5||j==10)for (int i = 0; i < 24; ++i, ++pexpl_[j]) {
			swprintf_s(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Explosion/expl_%02d_00,%02d), j+1, i);		
			loadimage(pexpl_[j], wcBuf, 0, 0, true);
		}
		else for(int i = 0; i < 32; ++i, ++pexpl_[j]) {
			swprintf_s(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Explosion/expl_%02d_00, %02d), j + 1, i);
			loadimage(pexpl_[j], wcBuf, 0, 0, true);
		}
	IMAGE* pexpl2_[] = { expl2_01,expl2_02,expl2_03,expl2_04,expl2_05,expl2_06,expl2_07,expl2_08,expl2_09,expl2_10,expl2_11 };
	
	for (int j = 0; j < 11; ++j)
		if (j == 0) for (int i = 0; i < 24; ++i, ++pexpl2_[j]) {
			swprintf_s(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Explosion/expl_%02d_00,%02d), j + 1, i);
			loadimage(pexpl2_[j], wcBuf, 128, 128, true);
		}
		else if (j < 5 || j == 10)for (int i = 0; i < 24; ++i, ++pexpl2_[j]) {
			swprintf_s(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Explosion/expl_%02d_00,%02d), j + 1, i);
			loadimage(pexpl2_[j], wcBuf, 128, 128, true);
		}
		else for (int i = 0; i < 32; ++i, ++pexpl2_[j]) {
			swprintf_s(wcBuf, COMBINE_FILENAME_MATERIAL_STR(PNG/Explosion/expl_%02d_00,%02d), j + 1, i);
			loadimage(pexpl2_[j], wcBuf, 128, 128, true);
		}
}