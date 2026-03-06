#pragma once
#include "Base/ObjectBase.h"

class Player :public ObjectBase {
private:
	//アニメーションの種類
	enum {
		eAnimIdle = 0,
		eAnimAttack,
		eAnimJump,
		eAnimDamage,
		eAnimDeath,
		eAnimRun,
	};

	CImage m_img;		//プレイヤーの画像
	bool m_flip;		//反転フラグ
	bool m_is_ground;	//接地判定
	int m_attack_no;	//攻撃番号
	int m_damage_no;	//ダメージ番号
	int m_hp;			//体力

	//状態
	enum {
		eState_Idle,
		eState_Attack1,
		eState_Attack2,
		eState_Damage1,
		eState_Damage2,
		eState_Down,
	};
	//状態変数
	int m_state;
	//各状態での挙動
	void StateIdle();

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