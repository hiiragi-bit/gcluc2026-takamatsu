#pragma once
#include "Base/ObjectBase.h"

//移動速度
#define MOVE_SPEED 8
//攻撃間隔
#define ATTACK_COOLDOWN_TIME 3.0f
//無敵時間
#define INVINCIBLE_TIME 1.0f

class Witch :public ObjectBase {
private:
	enum class EState {
		Idle,
		Run,
		Attack,
		Damage,
		Death,
	};
	CImage m_img;
	int m_state;
	int m_hp;
	float m_invincibleCnt;		//無敵時間カウント
	float m_cooldownCnt;		//攻撃間隔カウント
	bool m_isGround;
	bool m_flip;
	CVector3D m_range;			//攻撃範囲
public:
	Witch(const CVector3D& pos);
	~Witch();
	void Update() override;
	void Draw() override;
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDeath();
	void TakeDamage(int damage);
	/// <summary>
	/// プレイヤーとの距離
	/// </summary>
	/// <param name="pos">自分の座標</param>
	/// <param name="range">測りたい距離</param>
	/// <returns></returns>
	bool RangePlayer(const CVector3D& pos, const CVector3D& range);
	static TexAnimData _anim_data[];
};