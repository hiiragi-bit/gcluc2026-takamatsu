#pragma once
#include "Base/ObjectBase.h"

//斬撃の与ダメージ
#define SLASH_DAMAGE 1

class Slash :public ObjectBase {
private:
	//CImage m_img;
	int m_attackNo;
	int m_cnt;			//仮
	CVector3D m_range;
public:
	Slash(const CVector3D& pos, int attack_no, const CVector3D& range);
	~Slash();
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