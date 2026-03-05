#include "Witch.h"
#include "Player.h"

int cnt = 0;
int emove = 0;

TexAnim _idle[] = {
	{0,2},
};
TexAnim _run[] = {
	{0,2},
};
TexAnim _attack[] = {
	{0,2},
};
TexAnim _damage[] = {
	{0,2},
};
TexAnim _death[] = {
	{0,2},
};
TexAnimData Witch::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_attack),
	ANIMDATA(_damage),
	ANIMDATA(_death),
};

Witch::Witch(const CVector3D& pos)
	: ObjectBase(eType_Enemy)
	, m_state((int)EState::Idle)
	, m_hp(100)
	, m_invincibleCnt(0.0f)
	, m_cooldownCnt(0.0f)
	, m_isGround(true)
	, m_flip(false)
	, m_range(CVector3D(100, 100, 100)) {
	m_img = COPY_RESOURCE("Witch", CImage);
	m_pos = pos;
	//m_img.ChangeAnimation((int)EState::Idle);
}

Witch::~Witch(){

}

void Witch::Update(){
	switch (m_state) {
	case (int)EState::Idle:
		StateIdle();
		break;
	case (int)EState::Attack:
		StateAttack();
		break;
	case (int)EState::Damage:
		StateDamage();
		break;
	case (int)EState::Death:
		StateDeath();
		break;
	}
}

void Witch::Draw(){
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Witch::StateIdle(){
	//移動フラグ
	bool move;
	//m_img.UpdateAnimation();
	
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		//プレイヤーのいる方向へ攻撃
		CVector3D pos = p->m_pos - m_pos;
		pos.Normalize();
		CVector3D vec = pos * MOVE_SPEED;

		//クールタイム中でなければ
		if (m_cooldownCnt == 0) {
			//プレイヤーが攻撃範囲内なら攻撃、範囲外なら近づく
			bool b = RangePlayer(m_pos, m_range);
			(b) ? m_state = (int)EState::Attack : m_pos += vec;
		}
		//クールタイム中は後ろに下がる
		else m_pos -= vec * 0.5;
		
		(p->m_pos.x > m_pos.x) ? m_flip = true : m_flip = false;
	}

	//(move) ? m_img.ChangeAnimation((int)EState::Run)
	//	: m_img.ChangeAnimation((int)EState::Idle);
}

void Witch::StateAttack(){
	//m_img.ChangeAnimation((int)EState::Attack);
	//弾生成
	m_cooldownCnt = ATTACK_COOLDOWN_TIME;
	//if (m_img.CheckAnimationEnd()) {
		m_state = (int)EState::Idle;
	//}
}

void Witch::StateDamage(){
	//m_img.ChangeAnimation((int)EState::Damage, false);
	//if (m_img.CheckAnimationEnd()) {
		m_state = (int)EState::Idle;
	//}
}

void Witch::StateDeath(){
	//m_img.ChangeAnimation((int)EState::Death, false);
	//if (m_img.CheckAnimationEnd()) {
		SetKill();
	//}
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
