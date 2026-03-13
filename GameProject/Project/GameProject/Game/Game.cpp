#include "Game.h"
#include "Title/Clear.h"

int Game::m_playerHp = 0;
bool Game::m_game = false;

Game::Game()
	: ObjectBase(eType_Scene)
	, m_cnt(0)
	, m_time(0){

}

void Game::Update(){
	if (m_game) {
		//³‚µ‚¢ŽžŠÔ‚É•ÏX
		int time = m_time;
		if (time >= 60) {
			int t = time / 60;
			time = 40 * t;
		}
		m_time += time;
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
