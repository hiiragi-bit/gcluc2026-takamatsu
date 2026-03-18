#include "Base/EnemyManager.h"
#include "Game.h"
#include "Title/Clear.h"
#include"Game/MapObject.h"
#include"Game/Field.h"
#include"Game/Map.h"
#include"Game/Hero.h"

int Game::m_time = 0;
bool Game::m_game = true;

Game::Game()
	: ObjectBase(eType_Scene)
	, m_cnt(0) {
	randomcnt = rand() % 3;
	objcnt = 0;
	EnemyManager::Instance();
	ObjectBase::Add(new Player(CVector3D(100, 0, 0), false));
	ObjectBase::Add(new Field());
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
	if (!m_game) {
		m_cnt = 0;
		if (m_cnt++ >= 120) { 
			KillAll();
			ObjectBase::Add(new Clear());
		}
	}
	else if (m_cnt++ >= 60) {
		m_time++;
		m_cnt = 0;
	}
}
