#include "Swordsman.h"
#include "Player.h"
#include "Shadow.h"
#include "Slash.h"

TexAnim _swordsman_idle[] = {
	{0,16},
	{1,16},
};
TexAnim _swordsman_run[] = {
	{19,8},
	{20,8},
};
TexAnim _swordsman_damage[] = {
	{38,16},
	{39,16},
};
TexAnim _swordsman_attack[] = {
	{57,8},
	{58,8},
	{59,8},
	{60,8},
};
TexAnim _swordsman_death[] = {
	{76,8},
	{77,8},
	{78,8},
};
TexAnimData Swordsman::_animData[] = {
	ANIMDATA(_swordsman_idle),
	ANIMDATA(_swordsman_run),
	ANIMDATA(_swordsman_damage),
	ANIMDATA(_swordsman_attack),
	ANIMDATA(_swordsman_death),
};

Swordsman::Swordsman(const CVector3D& pos)
	: ObjectBase(eType_Swordsman)
	, m_state((int)EState::Idle)
	, m_hp(3)
	, m_attackNo(rand())
	, m_damageNo(-1)
	, m_invincibleCnt(0.0f)
	, m_cooldownCnt(0.0f)
	, m_isGround(true)
	, m_flip(false)
	, m_range(CVector3D(170, 10, 85)) {
	m_img = COPY_RESOURCE("Swordsman", CImage);
	m_pos = pos;
	m_img.ChangeAnimation((int)EState::Idle);
	m_rect = CRect(-48, -112, 48, 0);
	ObjectBase::Add(new Shadow(m_pos, eType_Swordsman));
}

Swordsman::~Swordsman() {

}

void Swordsman::Update() {
	if (ObjectBase::FindObject(eType_Player)) {
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
			m_attackNo++;
			break;
		case (int)EState::Death:
			StateDeath();
			break;
		}
	}

	m_pos += m_vec;
	//重力による落下
	m_vec.y += GRAVITY;

	if (m_pos.y <= 0) {
		m_pos.y = 0;
		m_vec.y = 0;
		m_isGround = true;
	}
	if (m_pos.z > MAX_Z) m_pos.z = MAX_Z;
	if (m_pos.z < MIN_Z) m_pos.z = MIN_Z;
}

void Swordsman::Draw() {
	m_img.SetRect(0, 0, 64, 64);
	m_img.SetSize(540, 540);
	m_img.SetCenter(270, 540 - 135);
	m_img.SetPos(CalcScreenPos());
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
		CVector3D pos = p->m_pos - m_pos;
		pos.Normalize();
		CVector3D vec = pos * SWORDSMAN_MOVE_SPEED;
		bool b = RangePlayer(m_pos, m_range);

		//クールタイム中でなく、プレイヤーが攻撃範囲内なら攻撃
		if (m_cooldownCnt == 0 && b) {
			m_state = (int)EState::Attack;
		}
		//クールダウン中かつ範囲外なら近づく
		else {
			if (!b) {
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
		//クールタイムが0なら攻撃
		if (m_cooldownCnt == 0 && m_img.CheckAnimationEnd()) {
			ObjectBase::Add(new Slash(m_pos, m_attackNo, m_range));
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

bool Swordsman::RangePlayer(const CVector3D& pos, const CVector3D& range){
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		CVector3D playerPos = p->m_pos;
		//自分とプレイヤーがrange以上ならfalse
		if (abs(pos.x - playerPos.x) > range.x) return false;
		if (abs(pos.y - playerPos.y) > range.y) return false;
		if (abs(pos.z - playerPos.z) > range.z) return false;

		return true;
	}
}
