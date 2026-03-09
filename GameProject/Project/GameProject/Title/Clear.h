#pragma once
#include "Base/Base.h"

class Clear :public Base {
	//画像オブジェクト
	CImage m_Clear;
	//待ち時間
	int m_cnt;

public:
	Clear();
	void Update();
	void Draw();
};