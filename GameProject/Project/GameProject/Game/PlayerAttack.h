#pragma once
#include "Base/ObjectBase.h"

class PlayerAttack :public ObjectBase
{
private:
	CImage m_img;		//プレイヤーの攻撃の画像
	bool m_flip;		//反転フラグ
	int m_attack_no;	//攻撃番号
	CVector2D m_vec;

public:
	//コンストラクタ
	PlayerAttack(const CVector3D& pos, bool flip, int type, int attack_no);
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//当たり判定
	void Collision(ObjectBase* b);

	//ダメージ番号の取得
	int GetAttackNo()
	{
		return m_attack_no;
	}
};