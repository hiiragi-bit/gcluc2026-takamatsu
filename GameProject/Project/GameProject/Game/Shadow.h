#pragma once
#include "Base/ObjectBase.h"

class Shadow :public ObjectBase {
private:
	CImage m_shadow;
	int m_type;
public:
	Shadow(const CVector3D& pos, int type);
	void Update() override;
	void Draw() override;
};