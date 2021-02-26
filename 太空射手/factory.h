#pragma once
#include"material.h"
#include"sprite.h"
#include"string"
#include"map"
#include<list>
#include<dsound.h>
#include<thread>
#pragma comment(lib, "winmm.lib")
class Factory;
//机体
extern SpriteBody Sprite_Ship1_blue;
extern SpriteBody Sprite_Ship1_green;
extern SpriteBody Sprite_Ship1_orange;
extern SpriteBody Sprite_Ship1_red;
extern SpriteBody Sprite_Ship2_blue;
extern SpriteBody Sprite_Ship2_green;
extern SpriteBody Sprite_Ship2_orange;
extern SpriteBody Sprite_Ship2_red;
extern SpriteBody Sprite_Ship3_blue;
extern SpriteBody Sprite_Ship3_green;
extern SpriteBody Sprite_Ship3_orange;
extern SpriteBody Sprite_Ship3_red;
extern SpriteBody Sprite_ufoBlue;
extern SpriteBody Sprite_ufoGreen;
extern SpriteBody Sprite_ufoRed;
extern SpriteBody Sprite_ufoYellow;
//战损
extern SpriteBody Sprite_Ship1_damage1;
extern SpriteBody Sprite_Ship1_damage2;
extern SpriteBody Sprite_Ship1_damage3;
extern SpriteBody Sprite_Ship2_damage1;
extern SpriteBody Sprite_Ship2_damage2;
extern SpriteBody Sprite_Ship2_damage3;
extern SpriteBody Sprite_Ship3_damage1;
extern SpriteBody Sprite_Ship3_damage2;
extern SpriteBody Sprite_Ship3_damage3;
//喷气，向下
extern SpriteBody Sprite_fire_1;
extern SpriteBody Sprite_fire_2;
extern SpriteBody Sprite_fire_3;
//向上
extern SpriteBody Sprite_fire_4;
extern SpriteBody Sprite_fire_5;
extern SpriteBody Sprite_fire_6;

extern SpriteBody Sprite_shield_1;
extern SpriteBody Sprite_shield_2;
extern SpriteBody Sprite_shield_3;
inline SpriteBody& GetShieldSprite(int level) {
	if (level <= 0)level = 1;
	switch (level) {
	case 1:return Sprite_shield_1;
	case 2:return Sprite_shield_2;
	case 3:return Sprite_shield_3;
	default:return Sprite_shield_3;
	}
}
//激光
extern SpriteBody Sprite_laserBlue01;
//激光爆炸
extern SpriteBody Sprite_laserflareBlue01;

//Enemies
extern SpriteBody Sprite_enemyBlack1;
extern SpriteBody Sprite_enemyBlack2;
extern SpriteBody Sprite_enemyBlack3;
extern SpriteBody Sprite_enemyBlack4;
extern SpriteBody Sprite_enemyBlack5;

extern SpriteBody Sprite_enemyBlue1;
extern SpriteBody Sprite_enemyBlue2;
extern SpriteBody Sprite_enemyBlue3;
extern SpriteBody Sprite_enemyBlue4;
extern SpriteBody Sprite_enemyBlue5;

extern SpriteBody Sprite_enemyGreen1;
extern SpriteBody Sprite_enemyGreen2;
extern SpriteBody Sprite_enemyGreen3;
extern SpriteBody Sprite_enemyGreen4;
extern SpriteBody Sprite_enemyGreen5;

extern SpriteBody Sprite_enemyRed1;
extern SpriteBody Sprite_enemyRed2;
extern SpriteBody Sprite_enemyRed3;
extern SpriteBody Sprite_enemyRed4;
extern SpriteBody Sprite_enemyRed5;
//Explosion
extern SpriteBody Sprite_expl_01;//64*64
extern SpriteBody Sprite_expl_02;//64*64
extern SpriteBody Sprite_expl_03;//64*64
extern SpriteBody Sprite_expl_04;//64*64
extern SpriteBody Sprite_expl_05;//32*32
extern SpriteBody Sprite_expl_06;//64*64
extern SpriteBody Sprite_expl_07;//32*32
extern SpriteBody Sprite_expl_08;//64*64
extern SpriteBody Sprite_expl_09;//128*128
extern SpriteBody Sprite_expl_10;//128*128
extern SpriteBody Sprite_expl_11;//96*96
//all 128*128
extern SpriteBody Sprite_expl2_01;
extern SpriteBody Sprite_expl2_02;
extern SpriteBody Sprite_expl2_03;
extern SpriteBody Sprite_expl2_04;
extern SpriteBody Sprite_expl2_05;
extern SpriteBody Sprite_expl2_06;
extern SpriteBody Sprite_expl2_07;
extern SpriteBody Sprite_expl2_08;
extern SpriteBody Sprite_expl2_09;
extern SpriteBody Sprite_expl2_10;
extern SpriteBody Sprite_expl2_11;


class Camp;
class Model;
class Bullet;
class Weapen;
class Ship;
class Factory;


class Camp {
public:
	enum class CAMP {
		Friendly,
		Enemy,
		Neutral
	};
	CAMP camp = CAMP::Friendly;
};
class Model : public Camp {
public:
	//Motran为模型映射数据
	//tran为模型真实坐标
	//不要随意改变，需要变动务必使用SetTran或者改变Tran后调用UpdateMoTran
	Transform MoTran;
	Transform Tran;
	Transform& SetTran(const Transform& tf) {
		Tran = tf;
		MoTran = Add(tf, -ModelRot);
		return MoTran;
	}
	void SetTranP(const Vec2D& p) {
		Tran.p = p;
		MoTran.p = p;
	}
	void SetTranQ(const Rot& q) {
		Tran.q = q;
		MoTran.q = Mul(q,-ModelRot);
	}
	void UpdateMoTran() {
		MoTran = Add(Tran, -ModelRot);
	}
	Rot ModelRot = Rot(PI / 2);//模型角度
	enum Status {
		Intact,
		Death = 1,
		Triggering = Death
	};
	//通过velocity，velocity_angular更新Tran和MoTran
	virtual void UpdateTran() {
		Tran.p += {velocity* Tran.q.c, -velocity* Tran.q.s};
		if (velocity_angular != 0) {
			Rot rot(velocity_angular);
			Tran.q = Mul(Tran.q, rot);
		}
		UpdateMoTran();
	}
	Status	 status	= Intact;
	LONGLONG die_time = 0;
	double	 velocity = 0;//线速度
	double	 velocity_angular = 0;//角速度
};


class Bullet : public Model {
	
public:
	virtual void DrawIntact(IMAGE* ImgDst) {
		if (status == Intact) {
			main_Body.Draw(ImgDst, MoTran);
		}
	}
	virtual void DrawDeath(IMAGE* ImgDst) {
		if (status == Death) {
			die_Body.Draw(ImgDst, MoTran);
		}
	}
	virtual void Draw(IMAGE* ImgDst) {
		if (status == Intact) {
			main_Body.Draw(ImgDst, MoTran);
			
		}
		else {
			die_Body.Draw(ImgDst, MoTran);
		}
	}
	virtual void DrawNormal(IMAGE* ImgDst) {
		if (status == Intact) {
			main_Body.DrawNormal(ImgDst, MoTran);

		}
		else {
			die_Body.DrawNormal(ImgDst, MoTran);
		}
	}
	void Hit(const Ship* ship, LONGLONG time) {
		HitShip = ship;
		Die(time);
	}
	void Die(LONGLONG time);
	int ID = 0;
	const Ship* HitShip = NULL;
	SpriteBody main_Body;
	SpriteBody die_Body;
	friend class Factory;
};
class Bullet_laserBlue01 : public Bullet {

	Bullet_laserBlue01(){
		ID = 12;
		main_Body = Sprite_laserBlue01;
		die_Body = Sprite_expl_03;//Sprite_laserflareBlue01;
	}
public:
	friend class Factory;
	friend class Weapen;
};

struct WeapensHole {
	Vec2D site;
	Weapen* weapen = NULL;
};
class Weapen:public Camp {
public:
	int ID = 0;
	Vec2D site;//坐标原点
	Rot rot;//偏向
	LONGLONG bullet_cd = LLONG_MAX;
	LONGLONG LastFiringTime = 0;
	bool  bSafetyLock = true;
	double Bullet_Velocity = 0;
	SpriteBody main_Body;//Or no
	Bullet* fire(Transform& tran);
};

class Weapen_laserBlue01:public Weapen {
public:
	Weapen_laserBlue01() {
		ID = 12;
		bSafetyLock = false;
		bullet_cd = TL::pHpte->PrecFrequency()/7;
		Bullet_Velocity = 10;
	}

};
struct Attribute {
	int HP = 0;
	int MaxHP = 0;
};
class Ship : public Model, public Attribute{
public:
	virtual void DrawIntact(IMAGE* ImgDst) {
		if (status == Intact) {
			main_Body.Draw(ImgDst, MoTran);
		}
	}
	virtual void DrawDeath(IMAGE* ImgDst) {
		if (status == Death) {
			die_Body.Draw(ImgDst, MoTran);
		}
	}
	virtual void Draw(IMAGE* ImgDst) {
		if (status == Intact) {
			main_Body.Draw(ImgDst, MoTran);

		}
		else {
			die_Body.Draw(ImgDst, MoTran);
		}
	}
	virtual void DrawNormal(IMAGE* ImgDst) {
		if (status == Intact) {
			main_Body.DrawNormal(ImgDst, MoTran);

		}
		else {
			die_Body.DrawNormal(ImgDst, MoTran);
		}
	}
	virtual void Die(LONGLONG time) {
		die_time = time;
		die_Body.map.SetBeginTime(time);
		status = Triggering;
		double move = main_Body.map.getFrame(TL::pHpte->getIntervals_int()).getheight() / 2;
		Tran.p += {Tran.q.c* move, -Tran.q.s * move};
		UpdateMoTran();
		std::thread([]() {
			mciSendString(_T("open E:\\文件夹\\WorkSpace\\桌面资料库/素材\\太空射手套件\\Bonus\\sfx_explosion04.wav alias mymusic"), NULL, 0, NULL);
			mciSendString(_T("seek mymusic to 0"), NULL, 0, NULL);
			mciSendString(_T("play mymusic"), NULL, 0, NULL);
			}).detach();
	}
	virtual void fire(std::list<Bullet*>&list) {
		bool play = false;
		for (auto& iter : weapenholes) {
			Bullet* temp = NULL;
			if (iter.weapen != NULL)temp = iter.weapen->fire(Tran);
			if (temp != NULL) {
				play = true;
				list.push_back(temp);
			}
		}
		//if(play)std::thread([]() {PlaySound(sfx_laser2, NULL, SND_ASYNC | SND_FILENAME | SND_NODEFAULT| SND_NOWAIT); }).detach();
	}
	virtual void SetShield(int level) {
		RemoveList(&shield);
		if (level <= 0) {
			shieldlevel = 0;
			main_Body.CalAABB();
			return;
		}
		switch (level) {
		case 1:shield = Sprite_shield_1; break;
		case 2:shield = Sprite_shield_2; break;
		case 3:shield = Sprite_shield_3; break;
		default:shield = Sprite_shield_3; break;
		}
		if (main_Body.son_sprite != NULL)InsertList_front(main_Body.son_sprite, (Sprite*)&shield);
		else main_Body.son_sprite = &shield;
		shieldlevel = level;
		main_Body.CalAABB();
	}
	virtual void SetDamage(int level) {
		RemoveList(&damage);
		if (level <= 0) {
			damagelevel = 0;
			main_Body.CalAABB();
			return;
		}
	}
	~Ship() {
		for (auto& iter : weapenholes) {
			if (iter.weapen != NULL)delete iter.weapen;
		}
	}
	SpriteBody main_Body;
	SpriteBody fire_left;
	SpriteBody fire_right;
	SpriteBody die_Body;
	SpriteBody damage;
	SpriteBody shield;
	int damagelevel = 0;
	int shieldlevel = 0;
	std::vector<WeapensHole> weapenholes;
	friend class Factory;
};

class Ship1_Bule :public Ship {
	Ship1_Bule() {
		main_Body = Sprite_Ship1_blue;
		fire_left = Sprite_fire_2;
		fire_right = Sprite_fire_2;
		fire_left.site = main_Body.tran.p + Vec2D(24, (double)64 + 5);
		fire_right.site = main_Body.tran.p + Vec2D(75, (double)64 + 5);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
		die_Body = Sprite_expl2_09;
		SetDamage(0);
		SetShield(3);
		weapenholes.resize(3);
		weapenholes[0].site = main_Body.tran.p + Vec2D(22, 33);
		weapenholes[0].weapen = new Weapen_laserBlue01;
		weapenholes[0].weapen->site = weapenholes[0].site;
		weapenholes[0].weapen->camp = camp;
		weapenholes[0].weapen->rot = Rot(PI / 16);
		weapenholes[1].site = main_Body.tran.p + Vec2D(76, 33);
		weapenholes[1].weapen = new Weapen_laserBlue01;
		weapenholes[1].weapen->site = weapenholes[1].site;
		weapenholes[1].weapen->camp = camp;
		weapenholes[1].weapen->rot = Rot(-PI / 16);

		weapenholes[2].site = main_Body.tran.p + Vec2D(49, 11);
		weapenholes[2].weapen = new Weapen_laserBlue01;
		weapenholes[2].weapen->site = weapenholes[2].site;
		weapenholes[2].weapen->camp = camp;
		MaxHP = 1;
		HP = MaxHP;
	}
public:
	virtual void SetDamage(int level) {
		RemoveList(&damage);
		if (level <= 0) {
			damagelevel = 0;
			main_Body.CalAABB();
			return;
		}
		switch (level) {
		case 1:damage = Sprite_Ship1_damage1; break;
		case 2:damage = Sprite_Ship1_damage2; break;
		case 3:damage = Sprite_Ship1_damage3; break;
		default:damage = Sprite_Ship1_damage3; break;
		}
		if (main_Body.son_sprite != NULL)InsertList_front(main_Body.son_sprite, (Sprite*)&damage);
		else main_Body.son_sprite = &shield;
		damagelevel = level;
	}
	virtual void fire(std::list<Bullet*>& list) {
		bool play = false;
		for (auto& iter : weapenholes) {
			Bullet* temp = NULL;
			if (iter.weapen != NULL)temp = iter.weapen->fire(Tran);
			if (temp != NULL) {
				play = true;
				list.push_back(temp);
			}
		}
		if (play)std::thread([]() {PlaySound(sfx_laser2, NULL, SND_ASYNC | SND_FILENAME | SND_NODEFAULT | SND_NOWAIT); }).detach();
	}
	friend class Factory;
};
class Ship1_Green :public Ship {
	Ship1_Green() {
		main_Body = Sprite_Ship1_green;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(24, (double)64 + 5);
		fire_right.site = main_Body.tran.p + Vec2D(75, (double)64 + 5);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};
class Ship1_Orange :public Ship {
	Ship1_Orange() {
		main_Body = Sprite_Ship1_orange;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(24, (double)64 + 5);
		fire_right.site = main_Body.tran.p + Vec2D(75, (double)64 + 5);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};
class Ship1_Red :public Ship {
	Ship1_Red() {
		main_Body = Sprite_Ship1_red;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(24, (double)64 + 5);
		fire_right.site = main_Body.tran.p + Vec2D(75, (double)64 + 5);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};
class Ship2_Bule :public Ship {
	Ship2_Bule() {
		main_Body = Sprite_Ship2_blue;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(34, (double)64 + 15);
		fire_right.site = main_Body.tran.p + Vec2D(79, (double)64 + 15);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};

class Ship2_Green :public Ship {
	Ship2_Green() {
		main_Body = Sprite_Ship2_green;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(34, (double)64 + 15);
		fire_right.site = main_Body.tran.p + Vec2D(79, (double)64 + 15);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};
class Ship2_Orange :public Ship {
	Ship2_Orange() {
		main_Body = Sprite_Ship2_orange;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(34, (double)64 + 15);
		fire_right.site = main_Body.tran.p + Vec2D(79, (double)64 + 15);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};
class Ship2_Red :public Ship {
	Ship2_Red() {
		main_Body = Sprite_Ship2_red;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(34, (double)64 + 15);
		fire_right.site = main_Body.tran.p + Vec2D(79, (double)64 + 15);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};
class Ship3_Bule :public Ship {
	Ship3_Bule() {
		main_Body = Sprite_Ship3_blue;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(19, (double)64 + 13);
		fire_right.site = main_Body.tran.p + Vec2D(79, (double)64 + 13);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};
class Ship3_Orange :public Ship {
	Ship3_Orange() {
		main_Body = Sprite_Ship3_orange;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(19, (double)64 + 13);
		fire_right.site = main_Body.tran.p + Vec2D(79, (double)64 + 13);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
}; class Ship3_Green :public Ship {
	Ship3_Green() {
		main_Body = Sprite_Ship3_green;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(19, (double)64 + 13);
		fire_right.site = main_Body.tran.p + Vec2D(79, (double)64 + 13);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
}; class Ship3_Red :public Ship {
	Ship3_Red() {
		main_Body = Sprite_Ship3_red;
		fire_left = Sprite_fire_1;
		fire_right = Sprite_fire_1;
		fire_left.site = main_Body.tran.p + Vec2D(19, (double)64 + 13);
		fire_right.site = main_Body.tran.p + Vec2D(79, (double)64 + 13);
		ConnectList(&fire_left, &fire_right);
		main_Body.son_sprite = &fire_left;
	}
public:
	friend class Factory;
};
class Ship_enemyRand :public Ship {
	Ship_enemyRand() {
		switch (rand() % 20) {
		case 0:main_Body = Sprite_enemyBlack1; velocity = (double)5 + rand() % 2;; MaxHP = rand() % 2 + 1; break;
		case 1:main_Body = Sprite_enemyBlack2; velocity = (double)5 + rand() % 2;; MaxHP = rand() % 2 + 2; break;
		case 2:main_Body = Sprite_enemyBlack3; velocity = (double)4 + rand() % 2;; MaxHP = rand() % 2 + 3; break;
		case 3:main_Body = Sprite_enemyBlack4; velocity = (double)4 + rand() % 2;; MaxHP = rand() % 2 + 4; break;
		case 4:main_Body = Sprite_enemyBlack5; velocity = (double)3 + rand() % 2;; MaxHP = rand() % 2 + 5; break;
		case 5:main_Body = Sprite_enemyBlue1;  velocity = (double)3 + rand() % 2;; MaxHP = rand() % 2 + 2; break;
		case 6:main_Body = Sprite_enemyBlue2;  velocity = (double)3 + rand() % 2;; MaxHP = rand() % 3 + 3; break;
		case 7:main_Body = Sprite_enemyBlue3;  velocity = (double)3 + rand() % 2;; MaxHP = rand() % 3 + 4; break;
		case 8:main_Body = Sprite_enemyBlue4;  velocity = (double)3 + rand() % 2;; MaxHP = rand() % 3 + 5; break;
		case 9:main_Body = Sprite_enemyBlue5;  velocity = (double)3 + rand() % 2;; MaxHP = rand() % 3 + 6; break;
		case 10:main_Body = Sprite_enemyGreen1; velocity = (double)2 + rand() % 2; MaxHP = rand() % 4 + 3; break;
		case 11:main_Body = Sprite_enemyGreen2; velocity = (double)2 + rand() % 2; MaxHP = rand() % 4 + 4; break;
		case 12:main_Body = Sprite_enemyGreen3; velocity = (double)2 + rand() % 2; MaxHP = rand() % 4 + 5; break;
		case 13:main_Body = Sprite_enemyGreen4; velocity = (double)2 + rand() % 2; MaxHP = rand() % 4 + 6; break;
		case 14:main_Body = Sprite_enemyGreen5; velocity = (double)2 + rand() % 2; MaxHP = rand() % 4 + 7; break;
		case 15:main_Body = Sprite_enemyRed1; velocity = (double)1 + rand() % 2; MaxHP = rand() % 5 + 4;  break;
		case 16:main_Body = Sprite_enemyRed2; velocity = (double)1 + rand() % 2; MaxHP = rand() % 6 + 5; break;
		case 17:main_Body = Sprite_enemyRed3; velocity = (double)1 + rand() % 2; MaxHP = rand() % 7 + 6; break;
		case 18:main_Body = Sprite_enemyRed4; velocity = (double)1 + rand() % 2; MaxHP = rand() % 8 + 7; break;
		case 19:main_Body = Sprite_enemyRed5; velocity = (double)1 + rand() % 2; MaxHP = rand() % 9 + 8; break;
		}

		switch (rand() % 11) {
		case 0:die_Body = Sprite_expl2_01; break;
		case 1:die_Body = Sprite_expl2_02; break;
		case 2:die_Body = Sprite_expl2_03; break;
		case 3:die_Body = Sprite_expl2_04; break;
		case 4:die_Body = Sprite_expl2_05; break;
		case 5:die_Body = Sprite_expl2_06; break;
		case 6:die_Body = Sprite_expl2_07; break;
		case 7:die_Body = Sprite_expl2_08; break;
		case 8:die_Body = Sprite_expl2_09; break;
		case 9:die_Body = Sprite_expl2_10; break;
		case 10:die_Body = Sprite_expl2_11; break;
		}
		ModelRot = Rot(-PI / 2);
		camp = CAMP::Enemy;
		//MaxHP = rand() % 10 + 1;
		HP = MaxHP;
	};
public:
	friend class Factory;

};

class Factory
{
	Factory() {
		factory_map["Ship1_Bule"] = 0;
		factory_map["Ship1_Green"] = 1;
		factory_map["Ship1_Orange"] = 2;
		factory_map["Ship1_Red"] = 3;
		factory_map["Ship2_Bule"] = 4;
		factory_map["Ship2_Green"] = 5;
		factory_map["Ship2_Orange"] = 6;
		factory_map["Ship2_Red"] = 7; 
		factory_map["Ship3_Bule"] = 8;
		factory_map["Ship3_Green"] = 9;
		factory_map["Ship3_Orange"] = 10;
		factory_map["Ship3_Red"] = 11;
		factory_map["Bullet_laserBlue01"] = 12;
		factory_map["Ship_enemyRand"] = 13;
		LoadSprite();
	};
	void LoadSprite();
public:
	static Factory* hInst() {
		static Factory hInstance;
		return &hInstance;
	}
	void* Creat(const char* name) {
		return Creat(factory_map[name]);
	}
	void* Creat(int n) {
		switch (n) {
		case 0: {
			return new Ship1_Bule;
		}break;
		case 1: {
			return new Ship1_Green;
		}break; 
		case 2: {
			return new Ship1_Orange;
		}break;
		case 3: {
			return new Ship1_Red;
		}break;
		case 4: {
			return new Ship2_Bule;
		}break;
		case 5: {
			return new Ship2_Green;
		}break;
		case 6: {
			return new Ship2_Orange;
		}break;
		case 7: {
			return new Ship2_Red;
		}break;
		case 8: {
			return new Ship3_Bule;
		}break;
		case 9: {
			return new Ship3_Green;
		}break;
		case 10: {
			return new Ship3_Orange;
		}break;
		case 11: {
			return new Ship3_Red;
		}break;
		case 12: {
			return new Bullet_laserBlue01;
		}break;
		case 13: {
			return new Ship_enemyRand;
		}break;

		default:return NULL;

		}
	}

	//friend class Weapen;
private:
	std::map<std::string, int> factory_map;
};

inline Bullet* Weapen::fire(Transform& tran) {
	const static Rot ModelRot = Rot(PI / 2);
	if (!bSafetyLock && LastFiringTime + bullet_cd < TL::pHpte->getIntervals_int()) {
		LastFiringTime = TL::pHpte->getIntervals_int();
		Bullet* ret = (Bullet*)Factory::hInst()->Creat(ID);
		ret->Tran.p = tran.p + Mul(ModelRot,Mul(-tran.q,site));
		ret->Tran.q = Mul(tran.q,rot);
		ret->UpdateMoTran();
		//temp->tran.q = Mul(Player_blue->tran.q, Rot(PI / 2));
		ret->velocity = Bullet_Velocity;
		ret->camp = camp;
		//temp->die_Body.map.SetIFS(TL::pHpte->PrecFrequency() / 8);
		ret->main_Body.CalAABB();
		return ret;
	}
	else return NULL;
}

