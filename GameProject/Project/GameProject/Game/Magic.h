#pragma once
#include "Base/ObjectBase.h"

//移動速度
#define MAGIC_SPEED 12
//魔法の与ダメージ
#define MAGIC_DAMAGE 1

class Magic :public ObjectBase {
private:
	CImage m_img;
	float m_ang;
public:
	Magic(const CVector3D& pos, float ang);
	~Magic();
	void Update() override;
	void Draw() override;
	void Collision(ObjectBase* o);
};