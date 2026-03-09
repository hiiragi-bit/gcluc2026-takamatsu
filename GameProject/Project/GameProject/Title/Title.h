#pragma once
#include "../Base/Base.h"

class Title :public Base {
	//画像オブジェクト
	CImage m_Title;
	//待ち時間
	int m_cnt;

public:
	Title();
	void Update();
	void Draw();
};