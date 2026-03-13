#pragma once
#include "Base/ObjectBase.h"

class Clear :public ObjectBase {
private:
	CImage m_img;
	CImage m_timer;
	int m_cnt;
	int m_time;
public:
	Clear();
	void Update() override;
	void Draw() override;
};