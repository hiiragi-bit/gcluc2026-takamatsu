#include "Enemy.h"

Enemy::Enemy(const CVector3D& pos):ObjectBase(eType_Enemy){
	//m_img = COPY_RESOURCE("Enemy", CImage);
	m_pos = pos;
}

void Enemy::Update()
{
}

void Enemy::Draw(){
	//m_img.SetPos(GetScreenPos(m_pos));
	//m_img.SetFlipH(true);
	//m_img.Draw();
}
