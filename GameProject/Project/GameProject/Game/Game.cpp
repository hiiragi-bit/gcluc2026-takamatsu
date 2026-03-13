#include "Game.h"
#include "Title/Clear.h"

int Game::m_playerHp = 0;
int Game::m_time = 0;
bool Game::m_game = false;

Game::Game()
	: ObjectBase(eType_Scene)
	, m_cnt(0) {

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
