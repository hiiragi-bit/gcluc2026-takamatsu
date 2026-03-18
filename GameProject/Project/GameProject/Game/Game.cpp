#include "Base/EnemyManager.h"
#include "Game.h"
#include "Title/Clear.h"
#include"Game/MapObject.h"
#include"Game/Field.h"
#include"Game/Map.h"
#include"Game/Hero.h"
#include "UI/HP.h"

int Game::m_damageCnt = 0;
int Game::m_deathCnt = 0;
int Game::m_time = 0;
bool Game::m_game = true;

Game::Game()
	: ObjectBase(eType_Scene)
	, m_cnt(0) 
	, m_hp(6) 
	, m_playerPos(0, 0, 0) {
	HP::UI_hp = 6;
	randomcnt = rand() % 3;
	objcnt = 0;
	EnemyManager::Instance();
	ObjectBase::Add(new Player(CVector3D(100, 0, 0), false));
	ObjectBase::Add(new Map());
	ObjectBase::Add(new HP(CVector3D(50, 50, 0)));
	ObjectBase::Add(new Hero(CVector3D(8000, 0, 3)));
	
	for (int i = 0; i < 5; i++) {
		
			ObjectBase::Add(new MapObject(CVector3D((objcnt + 900), 0, 1 ), eType_Well, randomcnt));
			ObjectBase::Add(new MapObject(CVector3D((objcnt + 200), 0, 2 ), eType_Fence, randomcnt));
			ObjectBase::Add(new MapObject(CVector3D((objcnt + 600), 0, 3 ), eType_Box, randomcnt));
		
		objcnt =+ 1000;
	}
}

void Game::Update(){
	//if (PUSH(CInput::eButton3))m_game = false;
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		m_playerPos = p->m_pos;
	}
	if (HP::UI_hp == 0 && !ObjectBase::FindObject(eType_Player)) {
		m_deathCnt++;
		HP::UI_hp = 6;
		m_hp = 6;
		ObjectBase::Add(new Player(CVector3D(m_playerPos.x - 100, 0, m_playerPos.z), false));
	}
	else if (HP::UI_hp != m_hp) {
		m_damageCnt++;
		m_hp = HP::UI_hp;
	}
	if (!m_game) {
KillAll();
		ObjectBase::Add(new Clear());	}
	else if (m_cnt++ >= 60) {
		m_time++;
		m_cnt = 0;
	}
}
