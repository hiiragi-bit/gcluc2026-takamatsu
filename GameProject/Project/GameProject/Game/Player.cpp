#include "Player.h"

static TexAnim _idle[] = {
	{0,5},
	{1,5},
	{2,5},
	{3,5},
};
static TexAnim _run[] = {
	{9,5},
	{10,5},
	{11,5},
	{12,5},
	{13,5},
	//{14,5},
};
static TexAnim _attack[] = {
	{17,5},
	{18,5},
	{19,5},
	//{20,5},
};
static TexAnim _jumpup[] = {
	{25,5},
	{26,5},
	//{27,5},
};
static TexAnim _jumpdouble[] = {
	{33,5},
	{34,5},
	//{35,5},
};
static TexAnim _jumpdown[] = {
	{41,5},
	{42,5},
	//{43,5},
};
static TexAnim _damage[] = {
	{49,5},
	{50,5},
	//{51,5},
};
static TexAnim _death[] = {
	{57,5},
	{58,5},
	{59,5},
	{60,5},
	{61,5},
	{62,5},
	{63,5},
	//{64,5},
};
TexAnimData Player::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_attack),
	ANIMDATA(_jumpup),
	ANIMDATA(_jumpdouble),
	ANIMDATA(_jumpdown),
	ANIMDATA(_damage),
	ANIMDATA(_death),
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
	m_img.SetCenter(90, 180);
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

void Player::StateIdle()
{
	//移動量
	const float move_speed = 6;
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
		move_flag = true;
	}
	//右移動
	if (HOLD(CInput::eRight))
	{
		//移動量を設定
		m_pos.x += move_speed;
		//反転フラグ
		m_flip = false;
		move_flag = true;
	}
	//上移動
	if (HOLD(CInput::eUp))
	{
		//移動量を設定
		m_pos.z += move_speed;
		//反転フラグ
		move_flag = true;
	}
	//下移動
	if (HOLD(CInput::eDown))
	{
		//移動量を設定
		m_pos.z -= move_speed;
		//反転フラグ
		move_flag = true;
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
		if (m_vec.y > 0)
			//上昇アニメーション
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//下降アニメーション
			m_img.ChangeAnimation(eAnimJumpDown, false);
	}
	//地面にいるなら
	else
	{
		if (move_flag)
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun);
		else
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle);
	}
}

void Player::Update()
{
	switch (m_state)
	{
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
	}
	m_pos_old = m_pos;
	//落ちていたら落下状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	if (m_pos.y >= 1080)
	{
		m_pos.y = 1080;
		m_vec.y = 1080;
		m_is_ground = true;
	}
	//アニメーション更新
	m_img.UpdateAnimation();
}

void Player::Draw(){
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//表示サイズ設定
	m_img.SetSize(180, 180);
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形
	//DrawRect();
}

void Player::Collision(ObjectBase* b)
{
}

void Player::TakeDamage(int damage)
{
}
