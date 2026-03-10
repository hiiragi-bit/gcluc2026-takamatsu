#include "Slash.h"
#include "Player.h"
#include "Swordsman.h"

Slash::Slash(const CVector3D& pos, int attack_no, int type, bool flip)
	:ObjectBase(eType_Effect)
	, m_attackNo(attack_no)
	, m_cnt(0)
	, m_flip(flip) {
	m_pos = pos;
	switch (type){
	case eType_Swordsman:
		m_rect = (!flip) ? CRect(-170, -200, -70, 70) : CRect(70, -200, 170, 70);
		break;
	case eType_Hero:
		m_rect = (!flip) ? CRect(-220, -200, -70, 70) : CRect(70, -200, 220, 70);
		break;
	}
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
