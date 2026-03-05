#pragma once
#include "Base/ObjectBase.h"

class Player :public ObjectBase {
private:
	CImage m_img;
public:
	Player(const CVector3D& pos);
	void Update();
	void Draw();
};