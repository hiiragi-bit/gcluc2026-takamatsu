#include "Slash.h"
#include "Player.h"
#include "Swordsman.h"

Slash::Slash(const CVector3D& pos, int attack_no, bool flip)
	:ObjectBase(eType_Effect)
	, m_attackNo(attack_no)
	, m_cnt(0)
	, m_flip(flip) {
	m_pos = pos;
	m_rect = (!flip) ? CRect(-170, -200, -70, 70) : CRect(70, -200, 170, 70);
}

Slash::~Slash()
{
}

void Slash::Update(){
	if (m_cnt++ >= 60) SetKill();
}

void Slash::Draw(){
	//DrawRect();
}

void Slash::Collision(ObjectBase* o){
	if (Player* p = dynamic_cast<Player*>(o)) {
		if (CollisionRect(this, p) && p->GetDamageNo()) {
			p->TakeDamage(SLASH_DAMAGE);
			p->SetDamageNo(m_attackNo);
		}
	}
}
