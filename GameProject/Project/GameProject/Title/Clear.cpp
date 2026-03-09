#include "Clear.h"
#include "Title/Title.h"
#include "Game/Game.h"
#include"Game/Map.h"
Clear::Clear() :Base(eType_Scene)
{
	m_Clear = COPY_RESOURCE("Clear", CImage);
	m_cnt = 0;
}

void Clear::Update()
{
	//ボタン1でタイトル破棄
	if (m_cnt++ > 2 && PUSH(CInput::eButton1)) {
		//全てのオブジェクトを破壊
		Base::KillAll();
		Map::s_map_data = {
    {
    CVector2D(MAP_TIP_SIZE * 5,800),
    CVector2D(MAP_TIP_SIZE * 26,800),
    CVector2D(MAP_TIP_SIZE * 42,800),
    },
    {
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    }
        };
		//タイトルシーンへ
		Base::Add(new Title());
	}
}

void Clear::Draw()
{
	m_Clear.SetSize(1920, 1080);
	m_Clear.SetPos(m_pos);
	m_Clear.Draw();
}