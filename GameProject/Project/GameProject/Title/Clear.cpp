#include "Clear.h"
#include "Game/Game.h"
#include "Title/Title.h"

Clear::Clear()
	: ObjectBase(eType_Scene)
	, m_cnt(0)
	, m_time(0) {
	m_sky = COPY_RESOURCE("Sky", CImage);
	m_ground = COPY_RESOURCE("Ground", CImage);
	m_timer = COPY_RESOURCE("Timer", CImage);
}

void Clear::Update() {
	//ボタン1でタイトル破棄
	if (m_cnt++ > 2 && PUSH(CInput::eButton1)) {
		//全てのオブジェクトを破壊
		ObjectBase::KillAll();
		ObjectBase::Add(new Title());
	}
}


void Clear::Draw(){
	m_sky.SetSize(1920, 1080);
	m_sky.Draw();
	m_ground.SetSize(1920, 1080);
	m_ground.Draw();

	//正しい時間に変更
	int time = Game::m_time;
	if (time >= 60) {
		int t = time / 60;
		m_time = 40 * t;
	}
	time += m_time;
	for (int i = 0;i < 5;i++) {
		if (i == 2) {
			m_timer.SetRect(910, 0, 1001, 103);
			m_timer.SetSize(91, 103);
			m_timer.SetPos(1192 - 91 * i, 600);
			m_timer.Draw();
			continue;
		}
		int m = time % 10;
		m_timer.SetRect(91 * m, 0, 91 + 91 * m, 103);
		m_timer.SetSize(91, 103);
		m_timer.SetPos(1192 - 91 * i, 600);
		m_timer.Draw();
		time /= 10;
	}
}