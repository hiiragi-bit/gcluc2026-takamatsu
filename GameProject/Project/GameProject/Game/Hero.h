#pragma once
#include "Base/EnemyBase.h"

//ˆÚ“®‘¬“x
#define HERO_MOVE_SPEED 6
//UŒ‚ŠÔŠu
#define HERO_ATTACK_COOLDOWN_TIME 120.0f
//–³“GŠÔ
#define HERO_INVINCIBLE_TIME 60.0f

class Hero :public EnemyBase {
private:
	enum class EState {
		Idle,
		Run,
		Damage,
		AttackSlash,
		AttackMagic,
		Death,
	};
	CImage m_img;
	CVector3D m_range;			//UŒ‚”ÍˆÍ
public:
	Hero(const CVector3D& pos);
	~Hero();
	void Update() override;
	void Draw() override;
	void StateIdle() override;
	void StateAttackSlash();
	void StateAttackMagic();
	void StateDamage() override;
	void StateDeath() override;
	void TakeDamage(int damage);
	/// <summary>
	/// –³“GŠÔ‚Ì”»’è
	/// </summary>
	/// <returns>–³“GŠÔ’†‚È‚çtrue</returns>
	bool GetInvncible() const {
		if (m_invincibleCnt != 0) return true;
		return false;
	}
	static TexAnimData _animData[];
};