#pragma once
#include "Base/EnemyBase.h"

//ˆÚ“®‘¬“x
#define WITCH_MOVE_SPEED 5
//UŒ‚ŠÔŠu
#define WITCH_ATTACK_COOLDOWN_TIME 120.0f
//–³“GŠÔ
#define WITCH_INVINCIBLE_TIME 60.0f

class Witch :public EnemyBase {
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
	Witch(const CVector3D& pos);
	~Witch();
	void Update() override;
	void Draw() override;
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDeath();
	void TakeDamage(int damage);
	static TexAnimData _animData[];
};