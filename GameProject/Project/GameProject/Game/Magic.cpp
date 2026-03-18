#include "Magic.h"
#include "Player.h"

TexAnim _magic[] = {
	{0,2},
	{1,2},
	{2,2},
	{1,2},
};
TexAnimData Magic::_animData[] = {
	ANIMDATA(_magic),
};

Magic::Magic(const CVector3D& pos, float ang)
	:ObjectBase(eType_Magic)
	, m_cnt(0)
	, m_ang(ang)
	, m_range(CVector3D(100, 5, 100)) {
	m_img = COPY_RESOURCE("Magic", CImage);
	m_pos = pos;
	m_vec = CVector3D(sin(ang), 0.0f, -cos(ang)) * MAGIC_SPEED;
	m_img.ChangeAnimation(0);
}

void Magic::Update(){
	m_img.UpdateAnimation();
	m_pos += m_vec;
	//3秒経つと削除
	if (m_cnt++ >= 180) SetKill();
}

void Magic::Draw(){
	m_img.SetSize(64, 64);
	m_img.SetCenter(32, 32);
	m_img.SetPos(CalcScreenPos());
	m_img.SetAng(-m_ang - DtoR(90));
	m_img.Draw();
}

void Magic::Collision(ObjectBase* o){
	if (Player* p = dynamic_cast<Player*>(o)) {
		if (RangePlayer(m_pos, m_range)) {
			p->TakeDamage(MAGIC_DAMAGE);
			SetKill();
		}
	}
}

bool Magic::RangePlayer(const CVector3D& pos, const CVector3D& range) {
	if (Player* p = dynamic_cast<Player*>(ObjectBase::FindObject(eType_Player))) {
		CVector3D playerPos = p->m_pos;
		//自分とプレイヤーがrange以上ならfalse
		if (abs(pos.x - playerPos.x) > range.x) return false;
		//if (abs(pos.y - playerPos.y) > range.y) return false;
		if (abs(pos.z - playerPos.z) > range.z) return false;

		return true;
	}
}
