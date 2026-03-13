#pragma once
#include "Base/ObjectBase.h"

class Game :public ObjectBase {
private:
	int m_cnt;
public:
	static int m_playerHp;			//プレイヤーのHp
	static int m_time;				//時間計測(秒)
	static bool m_game;				//ゲームクリア判定
	Game();
	void Update() override;
};