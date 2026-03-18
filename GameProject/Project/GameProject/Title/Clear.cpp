#include "Clear.h"
#include "Game/Game.h"
#include "Title/Title.h"
#include "UI/HP.h"

Clear::Clear()
	: ObjectBase(eType_Scene)
	, m_time(0) {
	m_result = COPY_RESOURCE("Result", CImage);
	m_sky = COPY_RESOURCE("Sky", CImage);
	m_ground = COPY_RESOURCE("Ground", CImage);
	m_timer = COPY_RESOURCE("Timer", CImage);
}

void Clear::Update() {
	if (ClickRect(350, 925, 830, 1010)) {
		SetKill();
		ObjectBase::Add(new Game());
	}
	if (ClickRect(1000, 1575, 830, 1010)) {
		SetKill();
		ObjectBase::Add(new Title());;
	}
}


void Clear::Draw(){
	m_sky.SetSize(1920, 1080);
	m_sky.Draw();
	m_ground.SetSize(1920, 1080);
	m_ground.Draw();
	m_result.Draw();

	int damage = Game::m_damageCnt;
	for (int i = 0;i < 3;i++, damage /= 10) {
		int m = damage % 10;
		m_timer.SetRect(91 * m, 0, 91 + 91 * m, 103);
		m_timer.SetSize(67.5f, 77.25f);
		m_timer.SetPos(1300 - 67.5f * i, 330);
		m_timer.Draw();
	}

	int death = Game::m_deathCnt;
	for (int i = 0;i < 3;i++, death /= 10) {
		int m = death % 10;
		m_timer.SetRect(91 * m, 0, 91 + 91 * m, 103);
		m_timer.SetSize(67.5f, 77.25f);
		m_timer.SetPos(1300 - 67.5f * i, 490);
		m_timer.Draw();
	}

	//³‚µ‚¢ŽžŠÔ‚É•ÏX
	int time = Game::m_time;
	if (time >= 60) {
		int t = time / 60;
		m_time = 40 * t;
	}
	time += m_time;
	for (int i = 0;i < 5;i++) {
		if (i == 2) {
			m_timer.SetRect(910, 0, 1001, 103);
			m_timer.SetSize(67.5f, 77.25f);
			m_timer.SetPos(1300 - 67.5f * i, 650);
			m_timer.Draw();
			continue;
		}
		int m = time % 10;
		m_timer.SetRect(91 * m, 0, 91 + 91 * m, 103);
		m_timer.SetSize(67.5f, 77.25f);
		m_timer.SetPos(1300 - 67.5f * i, 650);
		m_timer.Draw();
		time /= 10;
	}
}

bool Clear::ClickRect(float min_x, float max_x, float min_y, float max_y){
	CVector2D mouse_pos = CInput::GetMousePoint();
	if (mouse_pos.x >= min_x && mouse_pos.x <= max_x &&
		mouse_pos.y >= min_y && mouse_pos.y <= max_y && PUSH(CInput::eMouseL)) {
		return true;
	}
	return false;
}