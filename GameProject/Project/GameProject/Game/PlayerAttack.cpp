#include "PlayerAttack.h"

//コンストラクタ
PlayerAttack::PlayerAttack(const CVector3D& pos, bool flip, int type, int attack_no)
	:ObjectBase(type)
{
	//画像複製
	m_img = COPY_RESOURCE("PlayerAttack", CImage);
	m_flip = flip;
	m_pos = pos;
	m_img.SetCenter(90, 100);
	m_rect = CRect(-100, -100, 100, 0);
	//再生アニメーション設定(非ループ)
	m_img.ChangeAnimation(0, false);
	//攻撃番号
	m_attack_no = attack_no;
}

//更新処理
void PlayerAttack::Update()
{
	m_img.UpdateAnimation();
	if (m_img.CheckAnimationEnd())
	{
		SetKill();
	}
}

//描画処理
void PlayerAttack::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetSize(180, 100);
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	DrawRect();
}

//当たり判定
void PlayerAttack::Collision(ObjectBase* b)
{
}
