#pragma once
#include "Base/ObjectBase.h"

class Clear :public ObjectBase {
	//画像オブジェクト
	CImage m_Clear;
	//待ち時間
	int m_cnt;

public:
	Clear();
	void Update();
	void Draw();
};