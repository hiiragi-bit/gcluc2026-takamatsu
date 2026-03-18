#pragma once
#include "Base/ObjectBase.h"

class Game :public ObjectBase {
private:
	int m_cnt;
int objcnt;
	int randomcnt;int m_hp;
	CVector3D m_playerPos;public:
	static int m_damageCnt;			//ダメージカウント
	static int m_deathCnt;			//死亡カウント
	static int m_time;				//時間計測(秒)
	static bool m_game;				//ゲームクリア判定

	Game();
	void Update() override;
};