#pragma once
#include "Base/EnemyBase.h"

//ˆÚ“®‘¬“x
#define SWORDSMAN_MOVE_SPEED 8
//UŒ‚ŠÔŠu
#define SWORDSMAN_ATTACK_COOLDOWN_TIME 60.0f
//–³“GŠÔ
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
	CVector3D m_range;			//UŒ‚”ÍˆÍ
public:
	Swordsman(const CVector3D& pos);
	~Swordsman();
	void Update() override;
	void Draw() override;
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDeath();
	void TakeDamage(int damage);
	static TexAnimData _animData[];
};