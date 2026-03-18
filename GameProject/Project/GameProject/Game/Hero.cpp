#include "Hero.h"
#include "Magic.h"
#include "Game.h"
#include "Player.h"
#include "Slash.h"

TexAnim _hero_idle[] = {
	{0,16},
	{1,16},
};
TexAnim _hero_run[] = {
	{19,8},
	{20,8},
};
TexAnim _hero_damage[] = {
	{38,16},
	{39,16},
};
TexAnim _hero_attack_slash[] = {
	{57,8},
	{58,8},
	{59,8},
	{60,8},
};
TexAnim _hero_attack_magic[] = {
	{76,8},
	{77,8},
	{78,8},
};
TexAnim _hero_death[] = {
	{114,8},
	{115,8},
	{116,8},
};
TexAnimData Hero::_animData[] = {
	ANIMDATA(_hero_idle),
	ANIMDATA(_hero_run),
	ANIMDATA(_hero_damage),
	ANIMDATA(_hero_attack_slash),
	ANIMDATA(_hero_attack_magic),
	ANIMDATA(_hero_death),
};

Hero::Hero(const CVector3D& pos)
	: EnemyBase(eType_Hero) {
	m_img = COPY_RESOURCE("Hero", CImage);
	m_pos = pos;
	m_range = CVector3D(300, 10, 150);
	m_state = ((int)EState::Idle);
	m_hp = 20;
	m_img.ChangeAnimation((int)EState::Idle);
	m_rect = CRect(-48, -112, 48, 0);
}

Hero::~Hero(){
	Game::m_game = true;
}

void Hero::Update(){
	if (ObjectBase::FindObject(eType_Player)) {
		m_img.UpdateAnimation();
		switch (m_state) {
		case (int)EState::Idle:
			StateIdle();
			break;
		case (int)EState::Damage:
			StateDamage();
			break;
		case (int)EState::AttackSlash:
			StateAttackSlash();
			m_attackNo++;
			break;
		case (int)EState::AttackMagic:
			StateAttackMagic();
			break;
		case (int)EState::Death:
			StateDeath();
			break;
		}
	}

	m_pos += m_vec;
	//重力による落下
	m_vec.y += GRAVITY;

	if (m_pos.x < ENEMY_MIN_X) m_pos.x = ENEMY_MIN_X;
	if (m_pos.y <= 0) {
		m_pos.y = 0;
		m_vec.y = 0;
		m_isGround = true;
	}
	if (m_pos.z > MAX_Z) m_pos.z = MAX_Z;
	if (m_pos.z < MIN_Z) m_pos.z = MIN_Z;
}

void Hero::Draw(){
	m_img.SetRect(0, 0, 64, 64);
	m_img.SetSize(540, 540);
	m_img.SetCenter(270, 540 - 135);
	m_img.SetPos(CalcScreenPos());
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Hero::StateIdle(){
	//移動フラグ
	bool move = false;
	if (m_cooldownCnt != 0) m_cooldownCnt--;
	if (m_invincibleCnt != 0) m_invincibleCnt--;

	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		//プレイヤーのいる方向へ移動
		CVector3D pos = p->m_pos - m_pos;
		pos.Normalize();
		CVector3D vec = pos * HERO_MOVE_SPEED;
		bool b = RangePlayer(m_pos, m_range);

		//クールタイム中でなければ
		if (m_cooldownCnt == 0) {
			//プレイヤーがm_range内なら斬撃、範囲外なら魔法
			(b) ? m_state = (int)EState::AttackSlash
				: m_state = (int)EState::AttackMagic;
		}
		//クールダウン中は近づく
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

void Hero::StateAttackSlash(){
	m_img.ChangeAnimation((int)EState::AttackSlash, false);
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		//クールタイムが0なら攻撃
		if (m_cooldownCnt == 0 && m_img.CheckAnimationEnd()) {
			ObjectBase::Add(new Slash(m_pos, m_attackNo, m_range));
			m_cooldownCnt = HERO_ATTACK_COOLDOWN_TIME;
			m_state = (int)EState::Idle;
		}
	}
}

void Hero::StateAttackMagic(){
	m_img.ChangeAnimation((int)EState::AttackMagic, false);
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
			m_cooldownCnt = HERO_ATTACK_COOLDOWN_TIME;
			m_state = (int)EState::Idle;
		}
	}
}

void Hero::StateDamage(){
	m_img.ChangeAnimation((int)EState::Damage, false);
	//無敵時間
	m_invincibleCnt = HERO_INVINCIBLE_TIME;
	if (m_img.CheckAnimationEnd()) {
		m_state = (int)EState::Idle;
	}
}

void Hero::StateDeath(){
	m_img.ChangeAnimation((int)EState::Death, false);
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}

void Hero::TakeDamage(int damage){
	if (m_hp == 0) return;
	if (m_hp - damage > 0) {
		m_hp -= damage;
		m_state = (int)EState::Damage;
	}
	else {
		m_hp = 0;
		m_state = (int)EState::Death;
	}
}
