#include "Clear.h"
#include "Title/Title.h"
#include"Game/Map.h"
Clear::Clear() :ObjectBase(eType_Scene)
{
	m_Clear = COPY_RESOURCE("Clear", CImage);
	m_cnt = 0;
}

void Clear::Update()
{
	//ボタン1でタイトル破棄
	if (m_cnt++ > 2 && PUSH(CInput::eButton1)) {
		//全てのオブジェクトを破壊
		ObjectBase::KillAll();
		
  
        };
		//タイトルシーンへ
		ObjectBase::Add(new Title());
	}


void Clear::Draw()
{
	m_Clear.SetSize(1920, 1080);
	m_Clear.SetPos(GetScreenPos(m_pos));
	m_Clear.Draw();
}