#include "Base/EnemyManager.h"
#include "Game.h"
#include "Title/Clear.h"

int Game::m_playerHp = 0;
int Game::m_time = 0;
bool Game::m_game = false;

Game::Game()
	: ObjectBase(eType_Scene)
	, m_cnt(0) {
	EnemyManager::Instance();
	ObjectBase::Add(new Player(CVector3D(100, 0, 0), false));
	ObjectBase::Add(new Map());
	ObjectBase::Add(new HP(CVector3D(50, 50, 0)));
	ObjectBase::Add(new MapObject(CVector3D(900, 0, 0), eType_Well, 1));
	ObjectBase::Add(new MapObject(CVector3D(200, 0, 2), eType_Fence, 3));
	ObjectBase::Add(new MapObject(CVector3D(600, 0, 3), eType_Box, 4));
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
