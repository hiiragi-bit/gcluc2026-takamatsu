#pragma once
#include "Base/EnemyBase.h"

//à⁄ìÆë¨ìx
#define SWORDSMAN_MOVE_SPEED 8
//çUåÇä‘äu
#define SWORDSMAN_ATTACK_COOLDOWN_TIME 120.0f
//ñ≥ìGéûä‘
#define SWORDSMAN_INVINCIBLE_TIME 60.0f

class Swordsman :public EnemyBase {
private:
	enum class EState {
		Idle,
		Run,
		Damage,
		Attack,
		Death,
	};
	CImage m_img;
public:
	Swordsman(const CVector3D& pos);
	~Swordsman();
	void Update() override;
	void Draw() override;
	void StateIdle() override;
	void StateAttack() override;
	void StateDamage() override;
	void StateDeath() override;
	void TakeDamage(int damage);
	static TexAnimData _animData[];
};