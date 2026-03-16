#include "HP.h"

int HP::UI_hp = 0;
HP::HP(const CVector3D& pos):ObjectBase(eType_UI){
	m_img = COPY_RESOURCE("Heart", CImage);
	m_pos = pos;
	
}

void HP::Update()
{


}

void HP::Draw(){
	m_img.SetSize(384,384);
	m_img.SetRect(32 * UI_hp, 0, 32 + 32 * UI_hp, 32);
	m_img.Draw();
	
}



	
