#pragma once
#include "Base/ObjectBase.h"

class Game :public ObjectBase {
private:
	int m_cnt;
	int m_time;						//時間計測
public:
	static int m_playerHp;			//プレイヤーのHp
	static bool m_game;				//ゲームクリア判定
	Game();
	void Update() override;
};