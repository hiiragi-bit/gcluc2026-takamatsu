#pragma once
#include "Base/ObjectBase.h"

class Title :public ObjectBase {
private:
	CImage m_img;
	int m_cnt;
public:
	Title();
	void Update() override;
	void Draw() override;
};