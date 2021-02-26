#include "world.h"
void World::PlayerRebirth(const char* ShipName) {
	if (Player_blue != NULL) {
		std::list<Ship*>::iterator Player_iter = std::find(Ships.begin(),Ships.end(), Player_blue);
		delete Player_blue;
		Ships.erase(Player_iter);
	}
	Player_blue = (Ship*)pFac->Creat(ShipName);
	Ships.insert(Ships.begin(),Player_blue);
	Player_blue->main_Body.CalAABB();
	Player_blue->Tran.p = { (double)CameraWidth / 2, (double)CameraHeight - 100 };
	Player_blue->Tran.q = Rot(-(Vec2D((double)msg.x, (double)msg.y) - Player_blue->Tran.p).Angle());
	Player_blue->UpdateMoTran();
}

void World::Init() {
	srand(TL::pHpte->PrecClock().QuadPart);
	pFac = Factory::hInst();
	pOutImg = GetWorkingImage();
	pOutHDC = GetImageHDC();
	memset(_text, 0, sizeof(WCHAR) * 100);
	PlayerRebirth("Ship1_Bule");
	//Player_blue = (Ship*)pFac->Creat("Ship1_Bule");
	m_Ship2_Orange = (Ship*)pFac->Creat("Ship2_Orange"); //m_Ship2_Orange->camp = Camp::CAMP::Enemy;
	//m_Ship3_Red = (Ship*)pFac->Creat("Ship3_Red");
	//Ships.push_back(Player_blue);
	Ships.push_back(m_Ship2_Orange);
	//Ships.push_back(m_Ship3_Red);
	//Player_blue->main_Body.CalAABB();
	m_Ship2_Orange->main_Body.CalAABB();
	//m_Ship3_Red->main_Body.CalAABB();

	//Player_blue->Tran.p = { 100,100 };		Player_blue->UpdateMoTran();
	m_Ship2_Orange->Tran.p = { 100,300 };	m_Ship2_Orange->UpdateMoTran();
	//m_Ship3_Red->Tran.p = { 300,100 };		m_Ship3_Red->UpdateMoTran();
	//改变喷气颜色
	/*Player_blue->fire_left.map = Sprite_fire_2.map;
	Player_blue->fire_right.map = Sprite_fire_2.map;*/
	//添加护盾
	//Player_blue->SetShield(1);
	//Player_blue->shield = GetShieldSprite(1);
	//InsertList_front(&Player_blue->fire_left, &Player_blue->shield);
}


void World::WorldUpdate() {

	//暂时不更新
	//Update Camera
	//CameraSite = WorldSite;
	CameraAABB.lowerBound = /*CameraSite*/Vec2D();
	CameraAABB.upperBound = /*CameraSite*/Vec2D() + Vec2D(CameraWidth, CameraHeight);
	Vec2D v(CameraBorderWidth, CameraBorderWidth);
	CameraBorderAABB.lowerBound = CameraAABB.lowerBound - v;
	CameraBorderAABB.upperBound = CameraAABB.upperBound + v;
	//背景
	ImgHatch(pOutImg, &Background_darkPurple, (int)CameraSite.x, (int)CameraSite.y);
	

	static LONGLONG AddEnemyLastTime = TL::pHpte->getIntervals_int();
	static LONGLONG AddEnemyIntervalTime = (LONGLONG)(TL::pHpte->PrecFrequency()/1.5);
	const LONGLONG Sec = TL::pHpte->PrecFrequency();
	static LONGLONG lastAdd = TL::pHpte->getIntervals_int();
	LONGLONG now = TL::pHpte->getIntervals_int();
	if (isPutEnemy)if (now - lastAdd > TL::pHpte->PrecFrequency() ) {
		lastAdd = now;
		AddEnemyIntervalTime = LONGLONG(AddEnemyIntervalTime * 0.995);
	}
	if (now > AddEnemyLastTime + AddEnemyIntervalTime&&isPutEnemy) {
		AddEnemyLastTime = now;
		if (Ships.size() < 100) {
			Ship* pEnemy = (Ship*)pFac->Creat("Ship_enemyRand");
			Vec2D Site;
			Site.x = rand() % (CameraWidth + 150);
			Site = Site + Vec2D(-75, -75);
			pEnemy->Tran.p = Site;
			pEnemy->UpdateMoTran();
			//pEnemy->velocity = (double)(rand() % 2) + 1;
			pEnemy->main_Body.CalAABB();
			Ships.push_back(pEnemy);
			/*bool isAppropriate = false;
			int iterations = 0;
			while (isAppropriate == false && iterations < 10) {
				Vec2D Site;
				Site.y = rand() % (CameraWidth + 150);
				Site = Site + Vec2D(-75, -75);
				pEnemy->Tran.p = Site;
				pEnemy->UpdateMoTran();
			}*/
			
		}
	}
	if(isPutEnemy)TextOut(pOutHDC, 0, 0, _text, swprintf_s(_text, L"Put enemy rate:%lf", (double)Sec / (double)AddEnemyIntervalTime ));
	else TextOut(pOutHDC, 0, 0, _text, swprintf_s(_text, L"Put enemy rate:0"));

	for (auto iter = Ships.begin(); iter != Ships.end();) {
		if ((*iter)->status == Model::Status::Intact) {
			if ((*iter)->camp == Camp::CAMP::Enemy) {

				if (Player_blue != NULL)(*iter)->Tran.q = Rot(-(Player_blue->Tran.p - (*iter)->Tran.p).Angle());
				(*iter)->UpdateTran();
				b2AABB b2 = { (*iter)->Tran.p,(*iter)->Tran.p };
				if (!CameraBorderAABB.Contains(b2)) {
					(*iter)->Tran.q = Mul((*iter)->Tran.q, Rot(PI));
					(*iter)->UpdateTran();
					(*iter)->UpdateTran();
				}
				//if (!CameraBorderAABB.Contains((*iter)->main_Body.CalAABB((*iter)->MoTran))) {
				//	//(*iter)->Die(TL::pHpte->getIntervals_int());
				//	delete (*iter);
				//	Ships.erase(iter++);
				//}
				//else ++iter;
				
			}
			++iter;
		}
		else {
			if (TL::pHpte->getIntervals_int() - (*iter)->die_time > TL::pHpte->PrecFrequency() * 1.5) {
				delete (*iter); 
				if (*iter == Player_blue)Player_blue = NULL;
				Ships.erase(iter++);
			}
			else {
				++iter;
			}
		}
	}
	for (auto iter = Bullets.begin(); iter != Bullets.end(); ) {
		if (1/*(*iter)->status == Bullet::Status::Intact*/) {
			(*iter)->UpdateTran();
			if (!CameraBorderAABB.Contains((*iter)->main_Body.CalAABB((*iter)->MoTran))) {
				//(*iter)->Die(TL::pHpte->getIntervals_int());
				delete (*iter);
				Bullets.erase(iter++);
			}
			else ++iter;
		}
		else {	//清理超时的死亡子弹
			if (TL::pHpte->getIntervals_int() - (*iter)->die_time > TL::pHpte->PrecFrequency() * 1.5) {
				delete (*iter);
				Bullets.erase(iter++);
			}
			else {
				++iter;
			}
		}
	}

	CameraDraw(pOutImg);
	ControlInput();
	Collision();
}
World::~World() {
	for (auto iter = Bullets.begin(); iter != Bullets.end(); ++iter) {
		if (*iter != NULL)delete* iter;
	}
	for (auto iter = Ships.begin(); iter != Ships.end(); ++iter) {
		if (*iter != NULL)delete* iter;
	}
}






void World::CameraDraw(IMAGE* ImgDst) {
	
	
	
	for (auto iter = Bullets.begin(); iter != Bullets.end(); ++iter) {
		(*iter)->DrawIntact(pOutImg);
	}
	for (auto iter = Ships.begin(); iter != Ships.end(); ++iter) {
		(*iter)->DrawIntact(pOutImg);
	}
	//死亡动画在最上面
	for (auto iter = Bullets.begin(); iter != Bullets.end(); ++iter) {
		(*iter)->DrawDeath(pOutImg);
	}
	for (auto iter = Ships.begin(); iter != Ships.end(); ++iter) {
		(*iter)->DrawDeath(pOutImg);
	}

	TextOut(pOutHDC, CameraWidth - 170, CameraHeight - 48, _text, swprintf_s(_text, L"Ship Num:%d", (int)Ships.size()));
	TextOut(pOutHDC, CameraWidth - 170, CameraHeight - 32, _text, swprintf_s(_text, L"Bullet Num:%d", (int)Bullets.size()));
	TextOut(pOutHDC, CameraWidth - 170, CameraHeight - 16, _text, swprintf_s(_text, L"Game time:%lfs", TL::pHpte->getIntervals_db()));

}
void World::ControlInput() {
	double angle = ((double)clock() / 1000 * 2 * PI / 8);
	if (MouseHit()) {
		msg = GetMouseMsg();
		FlushMouseMsgBuffer();
	}
	Vec2D v = Vec2D((double)msg.x, (double)msg.y);

	m_Ship2_Orange->Tran.q = Rot(-(v - m_Ship2_Orange->Tran.p).Angle()); m_Ship2_Orange->UpdateMoTran();
	if (Player_blue != NULL && Player_blue->status != Model::Death) { Player_blue->Tran.q = Rot(-(v - Player_blue->Tran.p).Angle()); Player_blue->UpdateMoTran(); }
	//m_Ship3_Red->Tran.q = Rot(angle); m_Ship3_Red->UpdateMoTran();

	if (KEYDOWN(49)) {
		if (Player_blue != NULL)Player_blue->SetDamage(0);
		/*RemoveList(&Player_blue->damage);
		Player_blue->damage = Sprite_Ship1_damage1;
		InsertList_front(&Player_blue->fire_left, &Player_blue->damage);*/
	}if (KEYDOWN(50)) {
		if (Player_blue != NULL)Player_blue->SetDamage(1);
	}if (KEYDOWN(51)) {
		if (Player_blue != NULL)Player_blue->SetDamage(2);
	}if (KEYDOWN(52)) {
		if (Player_blue != NULL)Player_blue->SetDamage(3);
	}
	if (KEYDOWN(53)) {
		if (Player_blue != NULL)Player_blue->SetShield(0);
		/*RemoveList(&Player_blue->shield);
		Player_blue->shield = Sprite_shield_1;
		InsertList_front(&Player_blue->fire_left, &Player_blue->shield);*/
	}if (KEYDOWN(54)) {
		if (Player_blue != NULL)Player_blue->SetShield(1);
		/*RemoveList(&Player_blue->shield);
		Player_blue->shield = Sprite_shield_2;
		InsertList_front(&Player_blue->fire_left, &Player_blue->shield);*/
	}if (KEYDOWN(55)) {
		if (Player_blue != NULL)Player_blue->SetShield(2);
	/*	RemoveList(&Player_blue->shield);
		Player_blue->shield = Sprite_shield_3;
		InsertList_front(&Player_blue->fire_left, &Player_blue->shield);*/
	}if (KEYDOWN(56)) {
		if (Player_blue != NULL)Player_blue->SetShield(3);
		/*Player_blue->damage = Sprite_Ship1_damage3;
		ConnectList(&Player_blue->damage, &Player_blue->fire_left);*/
	}if (KEYDOWN(112)) {
		TL::pHpte->Pause();
	}
	if (KEYDOWN(113)) {
		TL::pHpte->Continue();
	}if (KEYDOWN(114)) {
		isPutEnemy = true;
	}if (KEYDOWN(115)) {
		isPutEnemy = false;
	}if (KEYDOWN(116)) {
		PlayerRebirth("Ship1_Bule");
	}
	if (KEYDOWN(32)) {
		if (Player_blue != NULL&& Player_blue->status!=Model::Death)Player_blue->fire(Bullets);
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
	if (GetKeyState(VK_CAPITAL))
	{
		//绘制法线
		/*Player_blue->main_Body.DrawNormal(GetWorkingImage(), Player_blue->MoTran);
		m_Ship2_Orange->main_Body.DrawNormal(GetWorkingImage(), m_Ship2_Orange->MoTran);*/
		//m_Ship3_Red->main_Body.DrawNormal(GetWorkingImage(), m_Ship3_Red->MoTran);

		////绘制AABB
		//DrawAABB(Player_blue->main_Body.CalAABB(Player_blue->MoTran));
		//DrawAABB(m_Ship2_Orange->main_Body.CalAABB(m_Ship2_Orange->MoTran));
		//DrawAABB(m_Ship3_Red->main_Body.CalAABB(m_Ship3_Red->MoTran));

		for (auto iter = Bullets.begin(); iter != Bullets.end(); ) {
			(*iter++)->DrawNormal(pOutImg);
		}
		for (auto iter = Ships.begin(); iter != Ships.end(); ) {
			if((*iter)->status != Model::Death)DrawAABB((*iter)->main_Body.CalAABB((*iter)->MoTran));
			(*iter++)->DrawNormal(pOutImg);
		}
		TextOut(pOutHDC, 0, CameraHeight - 16, _text, swprintf_s(_text, L"Display Normals")); 

	}
	if (Player_blue != NULL&& Player_blue->status!=Model::Death) {
		if (KEYDOWN(83))Player_blue->Tran.p.y += 3;
		if (KEYDOWN(87))Player_blue->Tran.p.y -= 3;
		if (KEYDOWN(68))Player_blue->Tran.p.x += 3;
		if (KEYDOWN(65))Player_blue->Tran.p.x -= 3;
		Player_blue->UpdateMoTran();
	}
	

}
void World::Collision() {
	/*if (TC::IsHit(Player_blue->main_Body.CalAABB(Player_blue->MoTran), m_Ship2_Orange->main_Body.CalAABB(m_Ship2_Orange->MoTran))
		|| TC::IsHit(Player_blue->main_Body.CalAABB(Player_blue->MoTran), m_Ship3_Red->main_Body.CalAABB(m_Ship3_Red->MoTran))
		) {
		TextOut(pOutHDC, 0, CameraHeight - 16, _text, swprintf_s(_text, L"AABB-Overlap"));
	}

	if (TC::IsHit(Player_blue->main_Body.SpriteShape, Player_blue->MoTran, m_Ship2_Orange->main_Body.SpriteShape, m_Ship2_Orange->MoTran)
		|| TC::IsHit(Player_blue->main_Body.SpriteShape, Player_blue->MoTran, m_Ship3_Red->main_Body.SpriteShape, m_Ship3_Red->MoTran)
		) {
		TextOut(pOutHDC, 0, CameraHeight - 32, _text, swprintf_s(_text, L"Hit"));
	}
	for (auto iter = Bullets.begin(); iter != Bullets.end(); iter++) {
		if ((*iter)->status == Bullet::Status::Intact) {
			if (TC::IsHit((*iter)->main_Body.CalAABB((*iter)->MoTran), m_Ship3_Red->main_Body.CalAABB(m_Ship3_Red->MoTran)))
				if (TC::IsHit((*iter)->main_Body.SpriteShape, (*iter)->MoTran, m_Ship3_Red->main_Body.SpriteShape, m_Ship3_Red->MoTran)) {
					(*iter)->Die(TL::pHpte->getIntervals_int());
				}
			if (TC::IsHit((*iter)->main_Body.CalAABB((*iter)->MoTran), m_Ship2_Orange->main_Body.CalAABB(m_Ship2_Orange->MoTran)))
				if (TC::IsHit((*iter)->main_Body.SpriteShape, (*iter)->MoTran, m_Ship2_Orange->main_Body.SpriteShape, m_Ship2_Orange->MoTran)) {
					(*iter)->Die(TL::pHpte->getIntervals_int());
				}
		}

	}
	settextcolor(RED);
	TextOut(pOutHDC, CameraWidth - 170, CameraHeight - 32, _text, swprintf_s(_text, L"Bullet Num:%d", (int)Bullets.size()));
	TextOut(pOutHDC, CameraWidth - 170, CameraHeight - 16, _text, swprintf_s(_text, L"Game time:%lfs", TL::pHpte->getIntervals_db()));*/

	for (auto& ibullet : Bullets) {
		if (ibullet->status == Bullet::Status::Intact) {
			b2AABB bulletAABB = ibullet->main_Body.CalAABB(ibullet->MoTran);
			for (auto& iship : Ships) {
				if (iship->status == Bullet::Status::Intact) {
					//如果阵营不同并且iship不是中立
					if (iship->camp != ibullet->camp && iship->camp != Camp::CAMP::Neutral) {
						if (TC::IsHit(bulletAABB, iship->main_Body.CalAABB(iship->MoTran)))
							if (TC::IsHit(ibullet->main_Body.SpriteShape, ibullet->MoTran, iship->main_Body.SpriteShape, iship->MoTran)) {
								ibullet->Hit(iship,TL::pHpte->getIntervals_int());
								if (iship->MaxHP != 0) {
									--iship->HP;
									if (iship->HP <= 0)iship->Die(TL::pHpte->getIntervals_int());
								}
							}
					}
				}
			}
		}
	}
	for (auto iter_src = Ships.begin(); iter_src != Ships.end(); ++iter_src) {
	
		if ((*iter_src)->status == Bullet::Status::Intact) {
			b2AABB srcAABB = (*iter_src)->main_Body.CalAABB((*iter_src)->MoTran);
			if (*iter_src == Player_blue&& Player_blue!=NULL) {
				for (auto iter = iter_src; iter != Ships.end(); ++iter) {
					if (iter == iter_src)continue;
					if ((*iter)->status == Bullet::Status::Intact) {
						if ((*iter_src)->camp == (*iter)->camp && (*iter)->camp == Camp::CAMP::Enemy)continue;
						if (TC::IsHit(srcAABB, (*iter)->main_Body.CalAABB((*iter)->MoTran)))
							if((*iter_src)->shieldlevel>0)
							{
								if (TC::IsHit((*iter_src)->shield.SpriteShape, (*iter_src)->MoTran, (*iter)->main_Body.SpriteShape, (*iter)->MoTran)) {
									if ((*iter)->MaxHP != 0) {
										(*iter)->Die(TL::pHpte->getIntervals_int());
									}
									(*iter_src)->SetShield(--(*iter_src)->shieldlevel);
								}
							}else if (TC::IsHit((*iter_src)->main_Body.SpriteShape, (*iter_src)->MoTran, (*iter)->main_Body.SpriteShape, (*iter)->MoTran)) {
								if ((*iter_src)->damagelevel < 3) {
									if ((*iter)->MaxHP != 0)(*iter)->Die(TL::pHpte->getIntervals_int());
									(*iter_src)->SetDamage(++(*iter_src)->damagelevel);
								}else{
									if ((*iter)->MaxHP != 0) {
										--(*iter)->HP;
										if ((*iter)->HP <= 0)(*iter)->Die(TL::pHpte->getIntervals_int());
									}

									if ((*iter_src)->MaxHP != 0) {
										--(*iter_src)->HP;
										if ((*iter_src)->HP <= 0) {
											(*iter_src)->Die(TL::pHpte->getIntervals_int());
											isPutEnemy = false;

											//player 死亡敌人方向随机
											for (auto &vi : Ships) {
												if (vi->camp == Camp::CAMP::Enemy) {
													vi->Tran.q = Rot((double)(rand() % 31415) / 10000.0);
													vi->UpdateMoTran();
												}
											}
										}
									}
								}
								
							}
					}
				}
			}
			else for (auto iter = iter_src; iter != Ships.end(); ++iter) {
				if (iter == iter_src)continue;
				if ((*iter)->status == Bullet::Status::Intact) {
					if ((*iter_src)->camp == (*iter)->camp && (*iter)->camp == Camp::CAMP::Enemy)continue;
					if (TC::IsHit(srcAABB, (*iter)->main_Body.CalAABB((*iter)->MoTran)))
						if (TC::IsHit((*iter_src)->main_Body.SpriteShape, (*iter_src)->MoTran, (*iter)->main_Body.SpriteShape, (*iter)->MoTran)) {
							if ((*iter)->MaxHP != 0) {
								--(*iter)->HP;
								if ((*iter)->HP <= 0)(*iter)->Die(TL::pHpte->getIntervals_int());
							}
							if ((*iter_src)->MaxHP != 0) {
								--(*iter_src)->HP;
								if ((*iter_src)->HP <= 0)(*iter_src)->Die(TL::pHpte->getIntervals_int());
							}
						}
				}
			}
		}
	}

}