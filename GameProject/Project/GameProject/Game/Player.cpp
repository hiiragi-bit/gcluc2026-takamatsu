#include "Player.h"

Player::Player(const CVector3D& pos):ObjectBase(eType_Player){
	//m_img = COPY_RESOURCE("Player", CImage);
	m_pos = pos;
}

void Player::Update()
{
}

void Player::Draw(){
	//m_img.SetPos(GetScreenPos(m_pos));
	//m_img.SetFlipH(false);
	//m_img.Draw();
}
