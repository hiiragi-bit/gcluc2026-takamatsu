#pragma once
#include "Base/ObjectBase.h"

//ˆÚ“®‘¬“x
#define HERO_MOVE_SPEED 10
//UŒ‚ŠÔŠu
#define HERO_ATTACK_COOLDOWN_TIME 120.0f
//–³“GŠÔ
#define HERO_INVINCIBLE_TIME 60.0f

class Hero :public ObjectBase {
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
	int m_state;
	int m_hp;
	int m_attackNo;
	int m_damageNo;
	float m_invincibleCnt;		//–³“GŠÔƒJƒEƒ“ƒg
	float m_cooldownCnt;		//UŒ‚ŠÔŠuƒJƒEƒ“ƒg
	bool m_isGround;
	bool m_flip;
	CVector3D m_range;			//UŒ‚”ÍˆÍ
public:
	Hero(const CVector3D& pos);
	~Hero();
	void Update() override;
	void Draw() override;
	void StateIdle();
	void StateAttackSlash();
	void StateAttackMagic();
	void StateDamage();
	void StateDeath();
	void SetDamageNo(int no) {
		m_damageNo = no;
	}
	int GetDamageNo() const {
		return m_damageNo;
	}
	void TakeDamage(int damage);
	/// <summary>
	/// –³“GŠÔ‚Ì”»’è
	/// </summary>
	/// <returns>–³“GŠÔ’†‚È‚çtrue</returns>
	bool GetInvncible() const {
		if (m_invincibleCnt != 0) return true;
		return false;
	}
	/// <summary>
	/// ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£
	/// </summary>
	/// <param name="pos">©•ª‚ÌÀ•W</param>
	/// <param name="range">‘ª‚è‚½‚¢‹——£</param>
	/// <returns></returns>
	bool RangePlayer(const CVector3D& pos, const CVector3D& range);
	static TexAnimData _animData[];
};