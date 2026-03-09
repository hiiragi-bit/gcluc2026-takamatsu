#include "Magic.h"
#include "Player.h"

Magic::Magic(const CVector3D& pos, float ang) :ObjectBase(eType_Magic) {
	m_img = COPY_RESOURCE("Magic", CImage);
	m_pos = pos;
	m_ang = ang;
	m_vec = CVector2D(sin(ang), cos(ang)) * MAGIC_SPEED;
}

Magic::~Magic()
{
}

void Magic::Update(){
	m_pos += m_vec;
	//スクリーン外に出ると削除
	if (m_pos.x - m_scroll.x < 0 || m_pos.x - m_scroll.x > SCREEN_WIDTH
		|| m_pos.y - m_scroll.y < 0 || m_pos.y - m_scroll.y > SCREEN_HEIGHT) SetKill();
}

void Magic::Draw(){
	m_img.SetSize(20, 100);
	m_img.SetCenter(10, 50);
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Magic::Collision(ObjectBase* o){
	if (Player* p = dynamic_cast<Player*>(o)) {
		if (CollisionRect(this, o)) {
			p->TakeDamage(MAGIC_DAMAGE);
			SetKill();
		}
	}
}
