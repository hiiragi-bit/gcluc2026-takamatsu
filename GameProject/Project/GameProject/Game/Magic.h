#pragma once
#include "Base/ObjectBase.h"

//移動速度
#define MAGIC_SPEED 12
//魔法の与ダメージ
#define MAGIC_DAMAGE 1

class Magic :public ObjectBase {
private:
	CImage m_img;
	int m_cnt;
	float m_ang;
	CVector3D m_range;
public:
	Magic(const CVector3D& pos, float ang);
	void Update() override;
	void Draw() override;
	void Collision(ObjectBase* o);
	/// <summary>
	/// プレイヤーとの距離
	/// </summary>
	/// <param name="pos">自分の座標</param>
	/// <param name="range">測りたい距離</param>
	/// <returns></returns>
	bool RangePlayer(const CVector3D& pos, const CVector3D& range);
};