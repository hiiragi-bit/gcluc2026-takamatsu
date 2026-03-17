#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Game/Swordsman.h"
#include "Game/Witch.h"

EnemyManager* EnemyManager::m_instance = nullptr;

EnemyManager::EnemyManager()
	: ObjectBase(eType_Scene)
	, m_enemyCnt(0)
	, m_enemyPos(CVector3D(900, 0, -200))
	, m_type(0) {

}

EnemyManager::~EnemyManager()
{
	if (m_instance == this)
	{
		m_instance = nullptr;
	}
}

void EnemyManager::Update()
{
	//生成上限に達していなければ
	if (m_enemyCnt <= MAX_ENEMY)
	{
		bool b = RangePlayer(m_enemyPos, SPAWN_RANGE);
		//プレイヤーが近くまで来たら
		if (b) {
			//m_typeに応じて敵を生成
			switch (m_type)
			{
			case 0:
				ObjectBase::Add(new Swordsman(m_enemyPos));
				m_type = 1;
				m_enemyPos.z = WITCH_SPAWN_Z;
				m_enemyCnt++;
				break;
			case 1:
				ObjectBase::Add(new Witch(m_enemyPos));
				m_type = 0;
				m_enemyPos = CVector3D(m_enemyPos.x + SPAWN_X, 0, SWORDSMAN_SPAWN_Z);
				m_enemyCnt++;
				break;
			}
		}
	}
}

void EnemyManager::Add(EnemyBase* enemy)
{
	m_enemies.push_back(enemy);
}

void EnemyManager::Remove(EnemyBase* enemy)
{
	auto itr = std::remove(m_enemies.begin(), m_enemies.end(), enemy);
	m_enemies.erase(itr, m_enemies.end());
}

EnemyManager* EnemyManager::Instance()
{
	// インスタンスがなければ、生成
	if (m_instance == nullptr)
	{
		m_instance = new EnemyManager();
		ObjectBase::Add(m_instance);
	}
	return m_instance;
}

EnemyBase* EnemyManager::GetNearEnemy(const CVector3D& pos, const CVector3D& range)
{
	// 生成済みの全ての敵の中から一番近い敵を探す
	EnemyBase* nearEnemy = nullptr;
	float nearDist = 0.0f;
	for (EnemyBase* enemy : m_enemies)
	{
		// 各軸の距離を求めて、範囲外であればスルー
		CVector3D enemyPos = enemy->m_pos;
		if (abs(pos.x - enemyPos.x) > range.x) continue;
		if (abs(pos.y - enemyPos.y) > range.y) continue;
		if (abs(pos.z - enemyPos.z) > range.z) continue;

		// 現在の一番近い敵より近い場合は、一番近い敵に設定
		float dist = (pos - enemyPos).Length();
		if (nearEnemy == nullptr || dist < nearDist)
		{
			nearEnemy = enemy;
			nearDist = dist;
		}
	}
	return nearEnemy;
}

bool EnemyManager::RangePlayer(const CVector3D& pos, const CVector3D& range)
{
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		CVector3D playerPos = p->m_pos;
		if (abs(pos.x - playerPos.x) > range.x) return false;
		//if (abs(pos.y - playerPos.y) > range.y) return false;
		if (abs(pos.z - playerPos.z) > range.z) return false;

		return true;
	}
}
