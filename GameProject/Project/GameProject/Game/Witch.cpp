#include "Witch.h"
#include "Magic.h"
#include "Player.h"

TexAnim _idle[] = {
	{0,16},
	{1,16},
};
TexAnim _run[] = {
	{19,8},
	{20,8},
	{21,8},
	{22,8},
};
TexAnim _damage[] = {
	{38,16},
	{39,16},
};
TexAnim _attack[] = {
	{57,8},
	{58,8},
	{59,8},
	{60,8},
};
TexAnim _death[] = {
	{76,8},
	{77,8},
	{78,8},
};
TexAnimData Witch::_animData[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_damage),
	ANIMDATA(_attack),
	ANIMDATA(_death),
};

Witch::Witch(const CVector3D& pos)
	: ObjectBase(eType_Witch)
	, m_state((int)EState::Idle)
	, m_hp(3)
	, m_invincibleCnt(0.0f)
	, m_cooldownCnt(0.0f)
	, m_isGround(true)
	, m_flip(false)
	, m_range(CVector3D(600, 600, 600)) {
	m_img = COPY_RESOURCE("Witch", CImage);
	m_pos = pos;
	m_img.ChangeAnimation((int)EState::Idle);
	m_rect = CRect(-48, -112, 48, 0);
}

Witch::~Witch(){

}

void Witch::Update(){
	m_img.UpdateAnimation();
	switch (m_state) {
	case (int)EState::Idle:
		StateIdle();
		break;
	case (int)EState::Damage:
		StateDamage();
		break;
	case (int)EState::Attack:
		StateAttack();
		break;
	case (int)EState::Death:
		StateDeath();
		break;
	}
	//落ちていたら落下状態へ移行
	if (m_isGround && m_vec.y > GRAVITY * 4)
		m_isGround = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	if (m_pos.y >= SCREEN_HEIGHT){
		m_pos.y = SCREEN_HEIGHT;
		m_isGround = true;
	}
}

void Witch::Draw(){
	m_img.SetRect(0, 0, 64, 64);
	m_img.SetSize(540, 540);
	m_img.SetCenter(270, 540 - 135);
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//DrawRect();
}

void Witch::StateIdle(){
	//移動フラグ
	bool move = false;
	if (m_cooldownCnt != 0) m_cooldownCnt--;
	if (m_invincibleCnt != 0) m_invincibleCnt--;

	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		//プレイヤーのいる方向へ移動
		CVector3D pos = GetScreenPos(p->m_pos) - GetScreenPos(m_pos);
		pos.Normalize();
		CVector3D vec = pos * WITCH_MOVE_SPEED;

		//クールタイム中でなければ
		if (m_cooldownCnt == 0) {
			//プレイヤーが攻撃範囲内なら攻撃、範囲外なら近づく
			bool b = RangePlayer(m_pos, m_range);
			if (b) {
				m_state = (int)EState::Attack;
			}
			else {
				m_pos += vec;
				move = true;
			}
		}
		
		(p->m_pos.x > m_pos.x) ? m_flip = true : m_flip = false;
	}

	(move) ? m_img.ChangeAnimation((int)EState::Run)
		: m_img.ChangeAnimation((int)EState::Idle);
}

void Witch::StateAttack(){
	m_img.ChangeAnimation((int)EState::Attack, false);
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		//攻撃方向
		CVector3D vec = GetScreenPos(p->m_pos) - GetScreenPos(m_pos);
		float ang = atan2(vec.x, vec.y);
		//クールタイムが0なら攻撃
		if (m_cooldownCnt == 0 && m_img.CheckAnimationEnd()) {
			//位置調整
			float posx = 0;
			float posy = -80;
			(!m_flip) ? posx = -40 : posx = 40;
			ObjectBase::Add(new Magic(CVector3D(m_pos.x + posx, m_pos.y + posy, m_pos.z), ang));
			m_cooldownCnt = WITCH_ATTACK_COOLDOWN_TIME;
			m_state = (int)EState::Idle;
		}
	}
}

void Witch::StateDamage(){
	m_img.ChangeAnimation((int)EState::Damage, false);
	//無敵時間
	m_invincibleCnt = WITCH_INVINCIBLE_TIME;
	if (m_img.CheckAnimationEnd()) {
		m_state = (int)EState::Idle;
	}
}

void Witch::StateDeath(){
	m_img.ChangeAnimation((int)EState::Death, false);
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}

void Witch::TakeDamage(int damage){
	if (m_hp - damage > 0) {
		m_hp -= damage;
		m_state = (int)EState::Damage;
	}
	else {
		m_hp = 0;
		m_state = (int)EState::Death;
	}
}

bool Witch::RangePlayer(const CVector3D& pos, const CVector3D& range)
{
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		CVector3D playerPos = p->m_pos;
		//自分とプレイヤーがrange以上ならfalse
		if (abs(pos.x - playerPos.x) > range.x) return false;
		if (abs(pos.y - playerPos.y) > range.y) return false;
		if (abs(pos.z - playerPos.z) > range.z) return false;

		return true;
	}
}

CVector2D Witch::CalcScreenPos(bool grounded) const
{
	CVector2D ret;

	// X座標はそのまま設定
	ret.x = m_pos.x;
	// 通常座標を求める場合
	if (!grounded)
	{
		// Y座標は、3次元座標のY（高さ）とZ（奥行）を合わせる
		float posZ = (SCREEN_HEIGHT * 0.75f) + m_pos.z;
		ret.y = -m_pos.y + posZ;
	}
	// 高さを考慮しない地面の位置を求める場合
	else
	{
		// Y座標は、3次元座標のZ（奥行）のみ反映する
		ret.y = (SCREEN_HEIGHT * 0.75f) + m_pos.z;
	}

	return ret;
}
