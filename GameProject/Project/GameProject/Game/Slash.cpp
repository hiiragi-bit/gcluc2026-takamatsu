#include "Slash.h"
#include "Player.h"
#include "Swordsman.h"

Slash::Slash(const CVector3D& pos, int attack_no, const CVector3D& range)
	:ObjectBase(eType_Effect)
	, m_attackNo(attack_no)
	, m_cnt(0)
	, m_range(range) {
	m_pos = pos;
}

Slash::~Slash()
{
}

void Slash::Update(){
	if (m_cnt++ >= 60) SetKill();
}

void Slash::Draw(){
	
}

void Slash::Collision(ObjectBase* o){
	if (Player* p = dynamic_cast<Player*>(o)) {
		if (RangePlayer(m_pos, m_range) && p->GetDamageNo() != m_attackNo) {
			p->TakeDamage(SLASH_DAMAGE);
			p->SetDamageNo(m_attackNo);
		}
	}
}

bool Slash::RangePlayer(const CVector3D& pos, const CVector3D& range) {
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		CVector3D playerPos = p->m_pos;
		//Ž©•ª‚ÆƒvƒŒƒCƒ„[‚ªrangeˆÈã‚È‚çfalse
		if (abs(pos.x - playerPos.x) > range.x) return false;
		//if (abs(pos.y - playerPos.y) > range.y) return false;
		if (abs(pos.z - playerPos.z) > range.z) return false;

		return true;
	}
}
