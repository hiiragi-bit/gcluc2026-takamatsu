#pragma once
#include "Base/ObjectBase.h"

class Enemy :public ObjectBase {
private:
	CImage m_img;
public:
	Enemy(const CVector3D& pos);
	void Update();
	void Draw();
};