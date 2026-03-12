#include "Shadow.h"
#include "Hero.h"
#include "Swordsman.h"
#include "Witch.h"
#include "Player.h"

Shadow::Shadow(const CVector3D& pos, int type)
	:ObjectBase(eType_Shadow)
	, m_type(type) {
	m_shadow = COPY_RESOURCE("Shadow", CImage);
	m_pos = pos;
}

void Shadow::Update(){
	switch (m_type){
	case eType_Hero:
		if (Hero* h = dynamic_cast<Hero*>(ObjectBase::FindObject(eType_Hero))) {
			m_pos = CVector3D(h->m_pos.x, 0, h->m_pos.z);
		}
		break;
	case eType_Swordsman:
		if (Swordsman* s = dynamic_cast<Swordsman*>(ObjectBase::FindObject(eType_Swordsman))) {
			m_pos = CVector3D(s->m_pos.x, 0, s->m_pos.z);
		}
		break;
	case eType_Witch:
		if (Witch* w = dynamic_cast<Witch*>(ObjectBase::FindObject(eType_Witch))) {
			m_pos = CVector3D(w->m_pos.x, 0, w->m_pos.z);
		}
		break;
	case eType_Player:
		if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
			m_pos = CVector3D(p->m_pos.x, 0, p->m_pos.z);
		}
		break;
	}
}

void Shadow::Draw(){
	m_shadow.SetSize(180, 270);
	m_shadow.SetCenter(90, 135);
	m_shadow.SetPos(CalcScreenPos(true));
	m_shadow.Draw();
}
