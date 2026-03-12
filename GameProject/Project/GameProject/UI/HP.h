#pragma once
#include "Base/ObjectBase.h"
#include"Game/Player.h"

class HP :public ObjectBase {
public:
	CImage m_img;
	int m_chengehp;
public:
	HP(const CVector3D& pos);
	void Update();
	void Draw();
	void ChengeHP(int hp);
};