#include "HP.h"

HP::HP(const CVector3D& pos):ObjectBase(eType_UI){
	m_img = COPY_RESOURCE("Heart", CImage);
	m_pos = pos;
}

void HP::Update()
{
}

void HP::Draw(){
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetSize(384,128);
	m_img.Draw();
}
