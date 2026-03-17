#pragma once
#include "Base/ObjectBase.h"
#include"Game/Player.h"

class HP :public ObjectBase {
public:
	CImage m_img;
	static int UI_hp ;
public:
	HP(const CVector3D& pos);
	void Update();
	void Draw();
};