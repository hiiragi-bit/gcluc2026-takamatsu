#pragma once
#include "Base/ObjectBase.h"

//ˆÚ“®‘¬“x
#define MOVE_SPEED 8
//UŒ‚ŠÔŠu
#define ATTACK_COOLDOWN_TIME 120.0f
//–³“GŠÔ
#define INVINCIBLE_TIME 60.0f

class Witch :public ObjectBase {
private:
	enum class EState {
		Idle,
		Run,
		Damage,
		Attack,
		Death,
	};
	CImage m_img;
	int m_state;
	int m_hp;
	float m_invincibleCnt;		//–³“GŠÔƒJƒEƒ“ƒg
	float m_cooldownCnt;		//UŒ‚ŠÔŠuƒJƒEƒ“ƒg
	bool m_isGround;
	bool m_flip;
	CVector3D m_range;			//UŒ‚”ÍˆÍ
public:
	Witch(const CVector3D& pos);
	~Witch();
	void Update() override;
	void Draw() override;
	void StateIdle();
	void StateDamage();
	void StateAttack();
	void StateDeath();
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
	CVector2D CalcScreenPos(bool grounded = false) const;
	static TexAnimData _anim_data[];
};