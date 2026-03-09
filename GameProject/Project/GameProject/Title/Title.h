#pragma once
#include "Base/ObjectBase.h"

class Title :public ObjectBase {
	//画像オブジェクト
	CImage m_Title;
	//待ち時間
	int m_cnt;

public:
	Title();
	void Update();
	void Draw();
};