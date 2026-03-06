#pragma once
#include "Base/ObjectBase.h"

class Player :public ObjectBase {
private:
	//アニメーションの種類
	enum {
		eAnimIdle = 0,		//待機アニメーション
		eAnimAttack,		//攻撃アニメーション
		eAnimDetransform,	//変身解除アニメーション
		eAnimJump,			//ジャンプアニメーション
		eAnimDeath,			//死亡アニメーション
		eAnimAbsorption,	//吸収アニメーション
		eAnimRun,			//走るアニメーション
		eAnimDamage,		//ダメージアニメーション
	};

	CImage m_img;		//プレイヤーの画像
	bool m_flip;		//反転フラグ
	bool m_is_ground;	//接地判定
	int m_attack_no;	//攻撃番号
	int m_damage_no;	//ダメージ番号
	int m_hp;			//体力

	//状態
	enum {
		eState_Idle,	//待機状態
		eState_Attack,	//攻撃状態
		eState_Damage,	//ダメージ状態
		eState_Death,	//死亡状態
	};
	//状態変数
	int m_state;
	//各状態での挙動
	void StateIdle();
	void StateAttack();

public:
	//コンストラクタ
	Player(const CVector3D& pos, bool flip);
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//当たり判定
	void Collision(ObjectBase* b);

	//ダメージ処理
	void TakeDamage(int damage);

	//ダメージ番号の取得
	int GetDamageNo() {
		return m_damage_no;
	}

	//ダメージ番号の設定
	void SetDamageNo(int no) {
		m_damage_no = no;
	}

	static TexAnimData _anim_data[];
};