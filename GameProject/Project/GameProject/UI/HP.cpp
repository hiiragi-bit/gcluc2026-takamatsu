#include "HP.h"

HP::HP(const CVector3D& pos):ObjectBase(eType_UI){
	m_img = COPY_RESOURCE("Heart", CImage);
	m_pos = pos;
}

void HP::Update()
{
	ChengeHP(0);
}

void HP::Draw(){
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetSize(384,384);
	m_img.Draw();
}
void HP::ChengeHP(int hp) { 
	m_img.SetRect(32 * hp, 0, 32 + 32*hp,32);
}
