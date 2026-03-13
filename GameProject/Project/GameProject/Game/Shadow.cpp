#include "Shadow.h"
#include "Player.h"

Shadow::Shadow(const CVector3D& pos, int type)
	:ObjectBase(eType_Shadow)
	, m_type(type) {
	m_shadow = COPY_RESOURCE("Shadow", CImage);
	m_pos = pos;
}

void Shadow::Update(){
	switch (m_type){
	case eType_Player:
		if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
			m_pos = CVector3D(p->m_pos.x, 0, p->m_pos.z);
		}
		break;
	}
}

void Shadow::Draw(){
	m_shadow.SetSize(480, 360);
	m_shadow.SetCenter(240, 230);
	m_shadow.SetPos(CalcScreenPos(true));
	m_shadow.Draw();
}
