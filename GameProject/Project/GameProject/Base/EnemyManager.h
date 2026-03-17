#pragma once
#include "Base/ObjectBase.h"

//生成上限
#define MAX_ENEMY 10
//感知範囲
#define SPAWN_RANGE CVector3D(500, 0, 250)
//敵生成時に加算するx
#define SPAWN_X 750
//剣士生成時のz
#define SWORDSMAN_SPAWN_Z -200
//魔法使い生成時のz
#define WITCH_SPAWN_Z 250

class EnemyBase;

class EnemyManager :public ObjectBase {
private:
	static EnemyManager* m_instance;	//インスタンス取得
	std::vector<EnemyBase*> m_enemies;	//エネミーリスト
	CVector3D m_enemyPos;				//エネミーの生成座標
	int m_enemyCnt;						//現在のエネミー生成数
	int m_type;							//0::Swordsman 1::Witch
	EnemyManager();
	~EnemyManager();
public:
	void Update() override;
	static EnemyManager* Instance();
	void Add(EnemyBase* enemy);
	void Remove(EnemyBase* enemy);
	/// <summary>
	/// 指定した位置から一番近い敵を取得
	/// </summary>
	/// <param name="pos">自分の座標</param>
	/// <param name="range">探索範囲</param>
	/// <returns>一番近い敵のアドレス</returns>
	EnemyBase* GetNearEnemy(const CVector3D& pos, const CVector3D& range);
	bool RangePlayer(const CVector3D& pos, const CVector3D& range);
};