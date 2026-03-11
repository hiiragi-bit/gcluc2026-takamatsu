#include "PlayerAttack.h"
#include "Witch.h"

static TexAnim _anim[] =
{
	{0,5},
	{1,5},
};

TexAnimData PlayerAttack::_anim_data[] =
{
	ANIMDATA(_anim),
};

//コンストラクタ
PlayerAttack::PlayerAttack(const CVector3D& pos, bool flip, int type, int attack_no)
	:ObjectBase(eType_Effect)
{
	//画像複製
	m_img = COPY_RESOURCE("PlayerAttack", CImage);
	//反転フラグ
	m_flip = flip;
	//座標設定
	m_pos = pos;
	//サイズ設定
	m_img.SetSize(1000, 1000);
	//中心位置設定
	m_img.SetCenter(90, 50);
	//当たり判定用矩形設定
	m_rect = CRect(-200, -200, 200, 200);
	//再生アニメーション設定(非ループ)
	m_img.ChangeAnimation(0, false);
	//攻撃番号
	m_attack_no = attack_no;
}

//更新処理
void PlayerAttack::Update()
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
void PlayerAttack::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	DrawRect();
}

//当たり判定
void PlayerAttack::Collision(ObjectBase* b)
{
	
	switch (b->m_type)
	{
	//魔法使いとの判定
	case eType_Witch:
		if (m_type == eType_Effect)
		{
			if (Witch* e = dynamic_cast<Witch*>(b))
			{
				if (CollisionRect(this, b))
				{
					e->TakeDamage(1);
				}
			}
		}
		break;
	}
}
