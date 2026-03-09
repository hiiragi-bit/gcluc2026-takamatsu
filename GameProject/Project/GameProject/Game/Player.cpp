#include "Player.h"

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
/*
static TexAnim _run[] = {
	{9,5},
	{10,5},
	{11,5},
	{12,5},
	{13,5},
	//{14,5},
};
*/

//ダメージアニメーション
/*
static TexAnim _damage[] = {
	{49,5},
	{50,5},
	{51,5},
};
*/

TexAnimData Player::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_attack),
	ANIMDATA(_detransform),
	ANIMDATA(_jump),
	ANIMDATA(_death),
	ANIMDATA(_absorption),
	//ANIMDATA(_run),
	//ANIMDATA(_damage),
};

Player::Player(const CVector3D& pos, bool flip)
	:ObjectBase(eType_Player)
{
	//画像複製
	m_img = COPY_RESOURCE("Player", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = pos;
	//中心位置設定
	m_img.SetCenter(270, 370);
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
	//当たり判定用矩形設定
	m_rect = CRect(0, 0, 0, 0);
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
	//体力
	//m_hp = 6;
}

//待機状態
void Player::StateIdle()
{
	//移動量
	const float move_speed = 8;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 15;

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

	//Cキーで攻撃
	if (PUSH(CInput::eButton3))
	{
		//変身解除状態へ移行
		m_state = eState_Detransform;
	}

	//SPACEキーでプレイヤーがジャンプ
	if (m_is_ground && PUSH(CInput::eButton5))
	{
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}
	//ジャンプ中なら
	if (!m_is_ground)
	{
		//上昇アニメーション
		m_img.ChangeAnimation(eAnimJump, false);
	}
	//地面にいるなら
	else
	{
		//待機アニメーション
		m_img.ChangeAnimation(eAnimIdle);
	}
}

//攻撃状態
void Player::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack, false);
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd())
	{
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

//吸収状態
void Player::StateAbsorption()
{
	//吸収アニメーションへ変更
	m_img.ChangeAnimation(eAnimAbsorption, false);
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd())
	{
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

//変身解除状態
void Player::StateDetransform()
{
	//変身解除アニメーションへ変更
	m_img.ChangeAnimation(eAnimDetransform, false);
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd())
	{
		//通常状態へ
		m_state = eState_Idle;
	}
}

//ダメージ状態
void Player::StateDamage()
{
}

//死亡状態
void Player::StateDeath()
{
	//死亡アニメーションへ変更
	m_img.ChangeAnimation(eAnimDeath, false);
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd())
	{
		//プレイヤーを削除
		SetKill();
	}
}

void Player::Update()
{
	m_pos_old = m_pos;

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
	}
	
	//落ちていたら落下状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;

	//プレイヤーのy座標が1080以上なら
	if (m_pos.y >= 1080)
	{
		//プレイヤーのy座標を1080にし、
		//接地判定をtrueにする
		m_pos.y = 1080;
		m_vec.y = 1080;
		m_is_ground = true;
	}

	//アニメーション更新
	m_img.UpdateAnimation();
}

//描画処理
void Player::Draw(){
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//表示サイズ設定
	m_img.SetSize(540, 540);
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形
	//DrawRect();
}

//当たり判定
void Player::Collision(ObjectBase* b)
{
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
