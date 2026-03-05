#pragma once
#include "Base/ObjectBase.h"

class HP :public ObjectBase {
	CImage m_img;
public:
	HP(const CVector3D& pos);
	void Update();
	void Draw();
};