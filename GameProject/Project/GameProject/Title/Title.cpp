#include "Title.h"
#include "Game/Game.h"

Title::Title()
	: ObjectBase(eType_Scene)
	, m_cnt(0) {
	m_img = COPY_RESOURCE("Title", CImage);
}

void Title::Update(){
	//ボタン10でタイトル破棄
	if (m_cnt++ > 2 && PUSH(CInput::eButton10)) {
		//全てのオブジェクトを破壊
		ObjectBase::KillAll();
		//ゲームシーンへ
		ObjectBase::Add(new Game());
	}
}

void Title::Draw(){
	m_img.SetSize(1920, 1080);
	//m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
}