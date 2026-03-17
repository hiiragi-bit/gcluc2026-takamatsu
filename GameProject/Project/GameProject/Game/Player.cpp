#include "Player.h"
#include "PlayerAttack.h"
#include "PlayerBullet.h"
#include "Shadow.h"
#include "Witch.h"
#include "Swordsman.h"
#include "Hero.h"
#include "UI/Weaponicon.h"

//待機アニメーション
static TexAnim _idle[] = {
	{0,10},
	{1,10},
};

//攻撃アニメーション
static TexAnim _attack[] = {
	{7,5},
	{8,5},
};

//変身解除アニメーション
static TexAnim _detransform[] = {
	{14,5},
	{15,5},
	{16,5},
};

//ジャンプアニメーション
static TexAnim _jump[] = {
	{21,5},
	{22,5},
	{23,5},
	{24,5},
	{25,5},
	{26,5},
};

//死亡アニメーション
static TexAnim _death[] = {
	{28,5},
	{29,5},
};

//吸収アニメーション
static TexAnim _absorption[] = {
	{35,5},
	{36,5},
	{37,5},
	{38,5},
};

//走るアニメーション
static TexAnim _run[] = {
	{42,5},
	{43,5},
	{44,5},
};

//ダメージアニメーション
static TexAnim _damage[] = {
	{28,5},
	{29,5},
};

TexAnimData Player::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_attack),
	ANIMDATA(_detransform),
	ANIMDATA(_jump),
	ANIMDATA(_death),
	ANIMDATA(_absorption),
	ANIMDATA(_run),
	ANIMDATA(_damage),
};

Player::Player(const CVector3D& pos, bool flip)
	:ObjectBase(eType_Player)
{
	//画像複製
	static char* mode_img[] = { "Player","PlayerWitch","PlayerSword","PlayerFighter"};
	for (int i = 0;i < eModeMax;i++) {
		m_imgList[i] = COPY_RESOURCE(mode_img[i], CImage);
		//再生アニメーション設定
		m_imgList[i].ChangeAnimation(0);
		//中心位置設定
		m_imgList[i].SetCenter(270, 370);
	}
	ObjectBase::Add(m_weapon_icon = new Weaponicon);
	//通常モードへ
	ChangeMode(eModeNormal);
	//再生アニメーション設定
	m_img->ChangeAnimation(0);
	//座標設定
	m_pos = pos;
	//中心位置設定
	m_img->SetCenter(270, 370);
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
	//当たり判定用矩形設定
	//m_rect = CRect(-110, -190, 100, 0);
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
	//体力
	m_hp = 6;
	ObjectBase::Add(new Shadow(m_pos, eType_Player));
}

//待機状態
void Player::StateIdle()
{
	//移動量
	const float move_speed = 8;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 25;

	//左移動
	if (HOLD(CInput::eLeft))
	{
		//移動量を設定
		m_pos.x -= move_speed;
		//反転フラグ
		m_flip = true;
		//移動フラグ
		move_flag = true;
	}

	//右移動
	if (HOLD(CInput::eRight))
	{
		//移動量を設定
		m_pos.x += move_speed;
		//反転フラグ
		m_flip = false;
		//移動フラグ
		move_flag = true;
	}

	//上移動
	if (HOLD(CInput::eUp))
	{
		//移動量を設定
		m_pos.z -= move_speed;
		//移動フラグ
		move_flag = true;
	}

	//下移動
	if (HOLD(CInput::eDown))
	{
		//移動量を設定
		m_pos.z += move_speed;
		//移動フラグ
		move_flag = true;
	}

	//Zキーで攻撃
	if (PUSH(CInput::eButton1))
	{
		//攻撃状態へ移行
		m_state = eState_Attack;
		m_attack_no++;
	}

	//Xキーで攻撃
	if (PUSH(CInput::eButton2))
	{
		//吸収状態へ移行
		m_state = eState_Absorption;
	}

	//Cキーで変身解除
	if (PUSH(CInput::eButton3))
	{
		//変身解除状態へ移行
		m_state = eState_Detransform;
	}

	//SPACEキーでプレイヤーがジャンプ
	if (m_is_ground && PUSH(CInput::eButton5))
	{
		m_vec.y = +jump_pow;
		m_is_ground = false;
	}
	//ジャンプ中なら
	if (!m_is_ground)
	{
		//ジャンプアニメーション
		m_img->ChangeAnimation(eAnimJump, false);
	}
	//地面にいるなら
	else
	{
		if (move_flag)
			//走るアニメーション
			m_img->ChangeAnimation(eAnimRun);
		else
			//待機アニメーション
			m_img->ChangeAnimation(eAnimIdle);
	}
}

//攻撃状態
void Player::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img->ChangeAnimation(eAnimAttack, false);
	if (m_mode == eModeWitch)
	{
		if (m_flip)
			ObjectBase::Add(new PlayerBullet(m_pos + CVector3D(-150, 100, 0), m_flip, eType_Effect,
				m_attack_no));
		else
			ObjectBase::Add(new PlayerBullet(m_pos + CVector3D(200, -100, -200), m_flip, eType_Effect,
				m_attack_no));
	}
	else
	{
		if (m_flip)
			ObjectBase::Add(new PlayerAttack(m_pos + CVector3D(-150, 100, 0), m_flip, eType_Effect,
				m_attack_no));
		else
			ObjectBase::Add(new PlayerAttack(m_pos + CVector3D(200, -100, -200), m_flip, eType_Effect,
				m_attack_no));
	}
	//アニメーションが終了したら
	if (m_img->CheckAnimationEnd())
	{
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

//吸収状態
void Player::StateAbsorption()
{
	//吸収アニメーションへ変更
	m_img->ChangeAnimation(eAnimAbsorption, false);
	//アニメーションが終了したら
	if (m_img->CheckAnimationEnd())
	{
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

//変身解除状態
void Player::StateDetransform()
{
	//変身解除アニメーションへ変更
	m_img->ChangeAnimation(eAnimDetransform, false);
	//アニメーションが終了したら
	if (m_img->CheckAnimationEnd())
	{
		ChangeMode(eModeNormal);
		//通常状態へ
		m_state = eState_Idle;
	}
}

//ダメージ状態
void Player::StateDamage()
{
	//ダメージアニメーションへ変更
	m_img->ChangeAnimation(eAnimDamage, false);
	//アニメーションが終了したら
	if (m_img->CheckAnimationEnd())
	{
		//通常状態へ
	m_state = eState_Idle;
	}
}

//死亡状態
void Player::StateDeath()
{
	//死亡アニメーションへ変更
	m_img->ChangeAnimation(eAnimDeath, false);
	//アニメーションが終了したら
	if (m_img->CheckAnimationEnd())
	{
		//プレイヤーを削除
		SetKill();
	}
}

void Player::Update()
{
	//状態の切り替え
	switch (m_state)
	{
	//待機状態
	case eState_Idle:
		StateIdle();
		break;
	//攻撃状態
	case eState_Attack:
		StateAttack();
		break;
	//吸収状態
	case eState_Absorption:
		StateAbsorption();
		break;
	//変身解除状態
	case eState_Detransform:
		StateDetransform();
		break;
	//ダメージ状態
	case eState_Damage:
		StateDamage();
		break;
	//死亡状態
	case eState_Death:
		StateDeath();
		break;
	}
	
	//落ちていたら落下状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;

	//プレイヤーのy座標が0未満なら
	if (m_pos.y < 0) 
	{
		//プレイヤーのy座標を0にし、
		//接地判定をtrueにする
		m_pos.y = 0;
		m_vec.y = 0;
		m_is_ground = true;
	}
	if (m_pos.z > MAX_Z) m_pos.z = MAX_Z;
	if (m_pos.z < MIN_Z) m_pos.z = MIN_Z;

	//スクロール設定
	m_scroll.x = m_pos.x - 1920 / 2;

	//アニメーション更新
	m_img->UpdateAnimation();
}

//描画処理
void Player::Draw(){
	//位置設定
	m_img->SetPos(CalcScreenPos());
	//表示サイズ設定
	m_img->SetSize(540, 540);
	//反転設定
	m_img->SetFlipH(m_flip);
	//描画
	m_img->Draw();
	//当たり判定矩形
	//DrawRect();
}

//当たり判定
void Player::Collision(ObjectBase* b)
{
	//Xキーで吸収
	if (PUSH(CInput::eButton2))
	{
		switch (b->m_type)
		{
		//魔法使いとの判定
		case eType_Witch:
			if (m_type == eType_Player)
			{
				if (Witch* w = dynamic_cast<Witch*>(b))
				{
					if (CollisionRect(this, b) && abs(m_pos.z - b->m_pos.z) < 64)
					{
						//魔法使いモードへ
						ChangeMode(eModeWitch);
						//w->SetKill();
					}
				}
			}
			break;
		//剣士との判定
		case eType_Swordsman:
			if (m_type == eType_Player)
			{
				if (Swordsman* s = dynamic_cast<Swordsman*>(b))
				{
					if (CollisionRect(this, b) && abs(m_pos.z - b->m_pos.z) < 64)
					{
						//剣士モードへ
						ChangeMode(eModeSword);
						//s->SetKill();
					}
				}
			}
			break;
		}
	}
}

//ダメージ処理
void Player::TakeDamage(int damage)
{
	//HP減少、下限0
	m_hp = max(m_hp - damage, 0);
	//HPが0以下なら
	if (m_hp <= 0)
	{
		//死亡状態へ移行
		m_state = eState_Death;
	}
	//HPが0以下でないなら
	else
	{
		//ダメージ状態へ移行
		m_state = eState_Damage;
	}
}
