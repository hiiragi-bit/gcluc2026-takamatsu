#include "Witch.h"
#include "Magic.h"
#include "Player.h"
#include "Shadow.h"

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
	: EnemyBase(eType_Witch)
	, m_range(CVector3D(600, 10, 300)) {
	m_img = COPY_RESOURCE("Witch", CImage);
	m_pos = pos;
	m_hp = 3;
	m_img.ChangeAnimation((int)EState::Idle);
	m_rect = CRect(-48, -112, 48, 0);
	ObjectBase::Add(new Shadow(m_pos, eType_Witch));
}

Witch::~Witch(){

}

void Witch::Update(){
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

void Witch::Draw(){
	m_img.SetRect(0, 0, 64, 64);
	m_img.SetSize(540, 540);
	m_img.SetCenter(270, 540 - 135);
	m_img.SetPos(CalcScreenPos());
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
		CVector3D pos = p->m_pos - m_pos;
		pos.Normalize();
		CVector3D vec = pos * WITCH_MOVE_SPEED;
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

void Witch::StateAttack(){
	m_img.ChangeAnimation((int)EState::Attack, false);
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		//攻撃方向
		CVector3D vec = p->m_pos - m_pos;
		vec.Normalize();
		float ang = atan2(vec.x, -vec.z);
		//クールタイムが0なら攻撃
		if (m_cooldownCnt == 0 && m_img.CheckAnimationEnd()) {
			//位置調整
			float posx = 0;
			float posy = 100;
			(!m_flip) ? posx = -120 : posx = 120;
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
