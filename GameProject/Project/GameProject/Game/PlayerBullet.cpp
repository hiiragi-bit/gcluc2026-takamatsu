#include "PlayerBullet.h"
#include "Witch.h"
#include "Swordsman.h"
#include "Hero.h"

TexAnim _bullet[] = {
	{2,2},
	{1,2},
	{0,2},
};

TexAnimData PlayerBullet::_anim_data[] = {
	ANIMDATA(_bullet),
};

//コンストラクタ
PlayerBullet::PlayerBullet(const CVector3D& pos, bool flip, int type, int attack_no)
	:ObjectBase(eType_Effect)
{
	//画像複製
	m_img = COPY_RESOURCE("PlayerBullet", CImage);
	//反転フラグ
	m_flip = flip;
	//座標設定
	m_pos = pos;
	//サイズ設定
	m_img.SetSize(64, 64);
	//中心位置設定
	m_img.SetCenter(32, 32);
	//当たり判定用矩形設定
	m_rect = CRect(-30, -10, 30, 10);
	//再生アニメーション設定(非ループ)
	m_img.ChangeAnimation(0);
	//攻撃番号
	m_attack_no = attack_no;
}

//更新処理
void PlayerBullet::Update()
{
	const int movespeed = 10;
	if (m_flip)
		m_pos.x -= movespeed;
	else
		m_pos.x += movespeed;
	if (m_pos.x < 0)
	{
		SetKill();
	}
	else if (m_pos.x > 1920)
	{
		SetKill();
	}
}

//描画処理
void PlayerBullet::Draw()
{
	m_img.SetPos(CalcScreenPos());
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	DrawRect();
}

//当たり判定
void PlayerBullet::Collision(ObjectBase* b)
{

	switch (b->m_type)
	{
		//魔法使いとの判定
	case eType_Witch:
		if (m_type == eType_Effect)
		{
			if (Witch* w = dynamic_cast<Witch*>(b))
			{
				if (CollisionRect(this, b) && abs(m_pos.z - b->m_pos.z) < 200)
				{
					w->TakeDamage(2);
				}
			}
		}
		break;
		//剣士との判定
	case eType_Swordsman:
		if (m_type == eType_Effect)
		{
			if (Swordsman* s = dynamic_cast<Swordsman*>(b))
			{
				if (CollisionRect(this, b) && abs(m_pos.z - b->m_pos.z) < 200)
				{
					s->TakeDamage(2);
				}
			}
		}
		break;
		//勇者との判定
	case eType_Hero:
		if (m_type == eType_Effect)
		{
			if (Hero* h = dynamic_cast<Hero*>(b))
			{
				if (CollisionRect(this, b) && abs(m_pos.z - b->m_pos.z) < 200)
				{
					h->TakeDamage(2);
				}
			}
		}
		break;
	}
}
