#include "Weaponicon.h"

Weaponicon::Weaponicon()
	:ObjectBase(eType_UI)
{
	static char* icon_img[] = { "NormalIcon","WitchIcon","SwordIcon","FighterIcon" };
	for (int i = 0;i < eIconMax;i++) 
	{
		m_imgList[i] = COPY_RESOURCE(icon_img[i], CImage);
	}
	ChangeIcon(eIconNormal);
}

void Weaponicon::Draw()
{
	m_img->SetSize(300, 300);
	m_img->SetPos(1600, 50);
	m_img->Draw();
}
