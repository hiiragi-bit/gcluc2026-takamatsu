#pragma once
#include "Base/ObjectBase.h"

class Weaponicon :public ObjectBase
{
public:
	//ÉÇÅ[ÉhÇÃéÌóﬁ
	enum {
		eIconNormal,
		eIconWitch,
		eIconSword,
		eIconFighter,
		eIconMax
	};

	int m_icon;
	CImage m_imgList[eIconMax];
	CImage* m_img;
	void ChangeIcon(int icon) {
		m_icon = icon;
		m_img = &m_imgList[m_icon];
	}

	Weaponicon();
	void Draw();
};