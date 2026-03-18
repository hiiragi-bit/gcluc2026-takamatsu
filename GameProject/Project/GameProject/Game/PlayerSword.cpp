#include "PlayerSword.h"
#include "Witch.h"
#include "Swordsman.h"
#include "Hero.h"

//コンストラクタ
PlayerSword::PlayerSword(const CVector3D& pos, bool flip, int type, int attack_no)
	:ObjectBase(eType_Effect)
{
	//反転フラグ
	m_flip = flip;
	//座標設定
	m_pos = pos;
	//当たり判定用矩形設定
	m_rect = CRect(-100, -100, 50, 50);
	//攻撃番号
	m_attack_no = attack_no;
}

//更新処理
void PlayerSword::Update()
{
	//アニメーション更新
	m_img.UpdateAnimation();
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd())
	{
		//削除
		SetKill();
	}
}

//描画処理
void PlayerSword::Draw()
{
	//DrawRect();
}

//当たり判定
void PlayerSword::Collision(ObjectBase* b)
{

	switch (b->m_type)
	{
		//魔法使いとの判定
	case eType_Witch:
		if (m_type == eType_Effect)
		{
			if (Witch* w = dynamic_cast<Witch*>(b))
			{
				if (m_attack_no != w->GetDamageNo() && CollisionRect(this, b)
					&& abs(m_pos.z - b->m_pos.z) < 200)
				{
					w->SetDamageNo(m_attack_no);
					w->TakeDamage(3);
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
				if (m_attack_no != s->GetDamageNo() && CollisionRect(this, b)
					&& abs(m_pos.z - b->m_pos.z) < 200)
				{
					s->SetDamageNo(m_attack_no);
					s->TakeDamage(3);
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
				if (m_attack_no != h->GetDamageNo() && CollisionRect(this, b)
					&& abs(m_pos.z - b->m_pos.z) < 200)
				{
					h->SetDamageNo(m_attack_no);
					h->TakeDamage(3);
				}
			}
		}
		break;
	}
}
