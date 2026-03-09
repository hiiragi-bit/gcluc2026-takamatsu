#include "Title.h"
#include "Game/Game.h"

Title::Title() :Base(eType_Scene)
{
	m_Title = COPY_RESOURCE("Title", CImage);
	m_cnt = 0;
}

void Title::Update()
{
	//ボタン1でタイトル破棄
	if (m_cnt++ > 2 && PUSH(CInput::eButton1)) {
		//全てのオブジェクトを破壊
		Base::KillAll();
		//ゲームシーンへ
		Base::Add(new Game());
	}
}

void Title::Draw()
{
	m_Title.SetSize(1920, 1080);
	m_Title.SetPos(m_pos);
	m_Title.Draw();
}