#include "EnemyBase.h"
#include "EnemyManager.h"

EnemyBase::EnemyBase(int type)
	: ObjectBase(type)
	, m_range(0, 0, 0)
	, m_state(0)
	, m_hp(0)
	, m_attackNo(rand())
	, m_damageNo(-1)
	, m_invincibleCnt(0.0f)
	, m_cooldownCnt(0.0f)
	, m_isGround(true)
	, m_flip(false) {
	EnemyManager::Instance()->Add(this);
	m_shadow = COPY_RESOURCE("Shadow", CImage);
}

EnemyBase::~EnemyBase()
{
	EnemyManager::Instance()->Remove(this);
}

void EnemyBase::Update()
{
}

void EnemyBase::PreDraw()
{
	m_shadow.SetSize(480, 360);
	m_shadow.SetCenter(240, 230);
	m_shadow.SetPos(CalcScreenPos(true));
	m_shadow.Draw();
}

void EnemyBase::Draw()
{
}

void EnemyBase::StateIdle()
{
}

void EnemyBase::StateAttack()
{
}

void EnemyBase::StateDamage()
{
}

void EnemyBase::StateDeath()
{
}

bool EnemyBase::RangePlayer(const CVector3D& pos, const CVector3D& range)
{
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		CVector3D playerPos = p->m_pos;
		//自分とプレイヤーがrange以上ならfalse(範囲外)
		if (abs(pos.x - playerPos.x) > range.x) return false;
		if (abs(pos.y - playerPos.y) > range.y) return false;
		if (abs(pos.z - playerPos.z) > range.z) return false;

		return true;
	}
}
