#pragma once
#include "Base/ObjectBase.h"

class Clear :public ObjectBase {
private:
	CImage m_result;
	CImage m_sky;
	CImage m_ground;
	CImage m_timer;
	int m_time;
public:
	Clear();
	void Update() override;
	void Draw() override;
	bool Clear::ClickRect(float min_x, float max_x, float min_y, float max_y);
};