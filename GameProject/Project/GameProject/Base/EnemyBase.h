#pragma once
#include "Base/ObjectBase.h"
#include "Game/Player.h"

//Xの下限
#define ENEMY_MIN_X 70

class EnemyBase :public ObjectBase {
public:
	CImage m_shadow;
	CVector3D m_range;			//攻撃範囲
	int m_state;
	int m_hp;
	int m_attackNo;
	int m_damageNo;
	float m_invincibleCnt;		//無敵時間カウント
	float m_cooldownCnt;		//攻撃間隔カウント
	bool m_isGround;
	bool m_flip;
public:
	EnemyBase(int type);
	virtual ~EnemyBase();
	void Update() override;
	void PreDraw() override;
	void Draw() override;
	virtual void StateIdle();
	virtual void StateAttack();
	virtual void StateDamage();
	virtual void StateDeath();
	void SetDamageNo(int no) {
		m_damageNo = no;
	}
	int GetDamageNo() const {
		return m_damageNo;
	}
	/// <summary>
	/// 無敵時間の判定
	/// </summary>
	/// <returns>無敵時間中ならtrue</returns>
	virtual bool GetInvncible() const {
		if (m_invincibleCnt != 0) return true;
		return false;
	}
	/// <summary>
	/// プレイヤーとの距離
	/// </summary>
	/// <param name="pos">自分の座標</param>
	/// <param name="range">測りたい距離</param>
	/// <returns></returns>
	virtual bool RangePlayer(const CVector3D& pos, const CVector3D& range);
};