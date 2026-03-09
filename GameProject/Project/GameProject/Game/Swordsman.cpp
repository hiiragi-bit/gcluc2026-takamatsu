#include "Swordsman.h"
#include "Player.h"

//TexAnim _idle[] = {
//	{0,16},
//	{1,16},
//};
//TexAnim _run[] = {
//	{19,8},
//	{20,8},
//	{21,8},
//	{22,8},
//};
//TexAnim _damage[] = {
//	{38,16},
//	{39,16},
//};
//TexAnim _attack[] = {
//	{57,8},
//	{58,8},
//	{59,8},
//	{60,8},
//};
//TexAnim _death[] = {
//	{76,8},
//	{77,8},
//	{78,8},
//};
//TexAnimData Swordsman::_animData[] = {
//	ANIMDATA(_idle),
//	ANIMDATA(_run),
//	ANIMDATA(_damage),
//	ANIMDATA(_attack),
//	ANIMDATA(_death),
//};

Swordsman::Swordsman(const CVector3D& pos)
	: ObjectBase(eType_Swordsman)
	, m_state((int)EState::Idle)
	, m_hp(3)
	, m_invincibleCnt(0.0f)
	, m_cooldownCnt(0.0f)
	, m_isGround(true)
	, m_flip(false)
	, m_range(CVector3D(120, 120, 120)) {
	m_img = COPY_RESOURCE("Swordsman", CImage);
	m_pos = pos;
	m_img.ChangeAnimation((int)EState::Idle);
	m_rect = CRect(-48, -112, 48, 0);
}

Swordsman::~Swordsman() {

}

void Swordsman::Update() {
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
	if (m_pos.y >= SCREEN_HEIGHT) {
		m_pos.y = SCREEN_HEIGHT;
		m_isGround = true;
	}
}

void Swordsman::Draw() {
	m_img.SetRect(0, 0, 64, 64);
	m_img.SetSize(512, 512);
	m_img.SetCenter(256, 512 - 128);
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//DrawRect();
}

void Swordsman::StateIdle() {
	//移動フラグ
	bool move = false;
	if (m_cooldownCnt != 0) m_cooldownCnt--;
	if (m_invincibleCnt != 0) m_invincibleCnt--;

	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		//プレイヤーのいる方向へ移動
		CVector3D pos = GetScreenPos(p->m_pos) - GetScreenPos(m_pos);
		pos.Normalize();
		CVector3D vec = pos * SWORDSMAN_MOVE_SPEED;

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

void Swordsman::StateAttack() {
	m_img.ChangeAnimation((int)EState::Attack, false);
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		//攻撃方向
		CVector3D vec = GetScreenPos(p->m_pos) - GetScreenPos(m_pos);
		float ang = atan2(vec.x, vec.y);
		//クールタイムが0なら攻撃
		if (m_cooldownCnt == 0 && m_img.CheckAnimationEnd()) {
			//攻撃::TODO
			m_cooldownCnt = SWORDSMAN_ATTACK_COOLDOWN_TIME;
			m_state = (int)EState::Idle;
		}
	}
}

void Swordsman::StateDamage() {
	m_img.ChangeAnimation((int)EState::Damage, false);
	//無敵時間
	m_invincibleCnt = SWORDSMAN_INVINCIBLE_TIME;
	if (m_img.CheckAnimationEnd()) {
		m_state = (int)EState::Idle;
	}
}

void Swordsman::StateDeath() {
	m_img.ChangeAnimation((int)EState::Death, false);
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}

void Swordsman::TakeDamage(int damage) {
	if (m_hp - damage > 0) {
		m_hp -= damage;
		m_state = (int)EState::Damage;
	}
	else {
		m_hp = 0;
		m_state = (int)EState::Death;
	}
}

bool Swordsman::RangePlayer(const CVector3D& pos, const CVector3D& range)
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
