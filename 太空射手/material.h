#pragma once
#include<graphics.h>
#include <Digitalv.h>  
#include <conio.h>
#pragma comment(lib, "winmm.lib")

#ifdef _UNICODE
#define NAME_TO_STR(name) L## #name
#else
#define NAME_TO_STR(name) (#name)
#endif
#define COMBINE2_STR(a,b) NAME_TO_STR(a##b)
#define COMBINE3_STR(a,b,c) NAME_TO_STR(a##b##c)

//Load all material
extern void load_material();


//Backgrounds
extern IMAGE Background_black;
extern IMAGE Background_blue;
extern IMAGE Background_darkPurple;
extern IMAGE Background_purple;

//PLAYER
extern IMAGE playerShip1_blue;
extern IMAGE playerShip1_green;
extern IMAGE playerShip1_orange;
extern IMAGE playerShip1_red;
extern IMAGE playerShip2_blue;
extern IMAGE playerShip2_green;
extern IMAGE playerShip2_orange;
extern IMAGE playerShip2_red;
extern IMAGE playerShip3_blue;
extern IMAGE playerShip3_green;
extern IMAGE playerShip3_orange;
extern IMAGE playerShip3_red;
extern IMAGE ufoBlue;
extern IMAGE ufoGreen;
extern IMAGE ufoRed;
extern IMAGE ufoYellow;

//Damage
extern IMAGE playerShip1_damage1;
extern IMAGE playerShip1_damage2;
extern IMAGE playerShip1_damage3;
extern IMAGE playerShip2_damage1;
extern IMAGE playerShip2_damage2;
extern IMAGE playerShip2_damage3;
extern IMAGE playerShip3_damage1;
extern IMAGE playerShip3_damage2;
extern IMAGE playerShip3_damage3;

//Effects

extern IMAGE fire[19];
extern IMAGE shield[3];
extern IMAGE speed;
extern IMAGE star[3];

//Enemies
extern IMAGE enemyBlack1;
extern IMAGE enemyBlack2;
extern IMAGE enemyBlack3;
extern IMAGE enemyBlack4;
extern IMAGE enemyBlack5;

extern IMAGE enemyBlue1;
extern IMAGE enemyBlue2;
extern IMAGE enemyBlue3;
extern IMAGE enemyBlue4;
extern IMAGE enemyBlue5;

extern IMAGE enemyGreen1;
extern IMAGE enemyGreen2;
extern IMAGE enemyGreen3;
extern IMAGE enemyGreen4;
extern IMAGE enemyGreen5;

extern IMAGE enemyRed1;
extern IMAGE enemyRed2;
extern IMAGE enemyRed3;
extern IMAGE enemyRed4;
extern IMAGE enemyRed5;

//Lasers
extern IMAGE laserBlue01;
extern IMAGE laserBlue02;
extern IMAGE laserBlue03;
extern IMAGE laserBlue04;
extern IMAGE laserBlue05;
extern IMAGE laserBlue06;
extern IMAGE laserBlue07;
extern IMAGE laserBlue08;
extern IMAGE laserBlue09;
extern IMAGE laserBlue10;
extern IMAGE laserBlue11;
extern IMAGE laserBlue12;
extern IMAGE laserBlue13;
extern IMAGE laserBlue14;
extern IMAGE laserBlue15;
extern IMAGE laserBlue16;


extern IMAGE laserGreen01;
extern IMAGE laserGreen02;
extern IMAGE laserGreen03;
extern IMAGE laserGreen04;
extern IMAGE laserGreen05;
extern IMAGE laserGreen06;
extern IMAGE laserGreen07;
extern IMAGE laserGreen08;
extern IMAGE laserGreen09;
extern IMAGE laserGreen10;
extern IMAGE laserGreen11;
extern IMAGE laserGreen12;
extern IMAGE laserGreen13;
extern IMAGE laserGreen14;
extern IMAGE laserGreen15;
extern IMAGE laserGreen16;

extern IMAGE laserRed01;
extern IMAGE laserRed02;
extern IMAGE laserRed03;
extern IMAGE laserRed04;
extern IMAGE laserRed05;
extern IMAGE laserRed06;
extern IMAGE laserRed07;
extern IMAGE laserRed08;
extern IMAGE laserRed09;
extern IMAGE laserRed10;
extern IMAGE laserRed11;
extern IMAGE laserRed12;
extern IMAGE laserRed13;
extern IMAGE laserRed14;
extern IMAGE laserRed15;
extern IMAGE laserRed16;


extern IMAGE meteorBrown_big1;
extern IMAGE meteorBrown_big2;
extern IMAGE meteorBrown_big3;
extern IMAGE meteorBrown_big4;
extern IMAGE meteorBrown_med1;
extern IMAGE meteorBrown_med3;
extern IMAGE meteorBrown_small1;
extern IMAGE meteorBrown_small2;
extern IMAGE meteorBrown_tiny1;
extern IMAGE meteorBrown_tiny2;
extern IMAGE meteorGrey_big1;
extern IMAGE meteorGrey_big2;
extern IMAGE meteorGrey_big3;
extern IMAGE meteorGrey_big4;
extern IMAGE meteorGrey_med1;
extern IMAGE meteorGrey_med2;
extern IMAGE meteorGrey_small1;
extern IMAGE meteorGrey_small2;
extern IMAGE meteorGrey_tiny1;
extern IMAGE meteorGrey_tiny2;


//Power_ups
extern IMAGE bold_silver;
extern IMAGE bolt_bronze;
extern IMAGE bolt_gold;
extern IMAGE pill_blue;
extern IMAGE pill_green;
extern IMAGE pill_red;
extern IMAGE pill_yellow;
extern IMAGE powerupBlue;
extern IMAGE powerupBlue_bolt;
extern IMAGE powerupBlue_shield;
extern IMAGE powerupBlue_star;
extern IMAGE powerupGreen;
extern IMAGE powerupGreen_bolt;
extern IMAGE powerupGreen_shield;
extern IMAGE powerupGreen_star;
extern IMAGE powerupRed;
extern IMAGE powerupRed_bolt;
extern IMAGE powerupRed_shield;
extern IMAGE powerupRed_star;
extern IMAGE powerupYellow;
extern IMAGE powerupYellow_bolt;
extern IMAGE powerupYellow_shield;
extern IMAGE powerupYellow_star;
extern IMAGE shield_bronze;
extern IMAGE shield_gold;
extern IMAGE shield_silver;
extern IMAGE star_bronze;
extern IMAGE star_gold;
extern IMAGE star_silver;
extern IMAGE things_bronze;
extern IMAGE things_gold;
extern IMAGE things_silver;

//UI
extern IMAGE buttonBlue;
extern IMAGE buttonGreen;
extern IMAGE buttonRed;
extern IMAGE buttonYellow;
extern IMAGE cursor;
extern IMAGE numeral0;
extern IMAGE numeral1;
extern IMAGE numeral2;
extern IMAGE numeral3;
extern IMAGE numeral4;
extern IMAGE numeral5;
extern IMAGE numeral6;
extern IMAGE numeral7;
extern IMAGE numeral8;
extern IMAGE numeral9;

extern IMAGE numeralX;
extern IMAGE playerLife1_blue;
extern IMAGE playerLife1_green;
extern IMAGE playerLife1_orange;
extern IMAGE playerLife1_red;
extern IMAGE playerLife2_blue;
extern IMAGE playerLife2_green;
extern IMAGE playerLife2_orange;
extern IMAGE playerLife2_red;
extern IMAGE playerLife3_blue;
extern IMAGE playerLife3_green;
extern IMAGE playerLife3_orange;
extern IMAGE playerLife3_red;

//“Ù–ß
extern const WCHAR* sfx_laser1;
extern const WCHAR* sfx_laser2;
extern const WCHAR* sfx_lose;
extern const WCHAR* sfx_shieldDown;
extern const WCHAR* sfx_shieldUp;
extern const WCHAR* sfx_twoTone;
extern const WCHAR* sfx_zap;
extern const WCHAR* sfx_explosion04;

//◊÷ÃÂ
extern const WCHAR* kenvector_future;
extern const WCHAR* kenvector_future_thin;






//Explosion
extern IMAGE expl_01[24];
extern IMAGE expl_02[24];
extern IMAGE expl_03[24];
extern IMAGE expl_04[24];
extern IMAGE expl_05[24];
extern IMAGE expl_06[32];
extern IMAGE expl_07[32];
extern IMAGE expl_08[32];
extern IMAGE expl_09[32];
extern IMAGE expl_10[32];
extern IMAGE expl_11[24];

//Explosion
extern IMAGE expl2_01[24];
extern IMAGE expl2_02[24];
extern IMAGE expl2_03[24];
extern IMAGE expl2_04[24];
extern IMAGE expl2_05[24];
extern IMAGE expl2_06[32];
extern IMAGE expl2_07[32];
extern IMAGE expl2_08[32];
extern IMAGE expl2_09[32];
extern IMAGE expl2_10[32];
extern IMAGE expl2_11[24];