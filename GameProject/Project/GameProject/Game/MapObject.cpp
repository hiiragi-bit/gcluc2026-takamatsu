#include "MapObject.h"
#include <vector>
#include <string>
#include <iostream>

// MapObject コンストラクタ
MapObject::MapObject(const CVector3D& pos,char objectname,int objectnb) : ObjectBase(objectname)
{
	CVector3D sc(m_scroll / 8);
	m_pos = pos;
	m_objectname = objectname;
	m_objectnb = objectnb;
	m_box = COPY_RESOURCE("Box", CImage);
	m_well = COPY_RESOURCE("Well", CImage);
	m_fence = COPY_RESOURCE("Fence", CImage);
	ObjectBase::Add(new Shadow(m_pos, eType_Fence));
	ChangeObject();
}
void MapObject::ChangeObject() 
{ 
	CVector3D sc(m_scroll / 8);
	//オブジェクトの種類に応じて画像を変更
	switch (m_objectname)
	{

	case eType_Box:
		//箱の画像の種類を設定
		switch (m_objectnb)
		{
		case 1:
			m_box.SetRect(0, 0, 24,32);
			m_box.SetSize(240,320);
			m_box.SetCenter(120, 160);
			break;
		case 2:
			m_box.SetRect(24, 0, 48, 32);
			m_box.SetSize(240,320);
			m_box.SetCenter(120, 160);
			break;
		case 3:
			m_box.SetRect(sc.x+48, 0, sc.x+72, 24);
			m_box.SetSize(240,240);
			m_box.SetCenter(120, 120);
			break;
		case 4:	
			m_box.SetRect(72, 0, 96, 24);
			m_box.SetSize(240,240);
			m_box.SetCenter(120, 120);
			break;
		case 5:	
			m_box.SetRect(96, 0, 120, 24);
			m_box.SetSize(240,240);
			m_box.SetCenter(120, 240);
			break;
		}
		break;
	case eType_Well:
		//井戸の画像の種類を設定
		switch (m_objectnb)
		{
		case 1:
			m_well.SetRect(0, 0, 48,48);
			break;
		case 2:
			m_well.SetRect(48, 0, 96, 48);
			break;
		case 3:
			m_well.SetRect(96, 0, 144, 48);
			break;
		}
		m_well.SetSize(320,320);
		m_well.SetCenter(160,300);
		break;
	case eType_Fence:
		//柵の画像の種類を設定
		switch (m_objectnb)
		{
			case 1:
				m_fence.SetRect(0, 0, 24, 24);
				break;
			case 2:
				m_fence.SetRect(24, 0, 48, 24);
				break;
			case 3:
				m_fence.SetRect(48, 0, 72, 24);
				break;
		}
		m_fence.SetSize(240,240);
		m_fence.SetCenter(120, 240);
		
		break;
		break;
	}
}
void MapObject::Update() {

}
void MapObject::Draw() {
	//スクロール設定
	
	//m_box.SetRect(sc.x, 0, sc.x + 150, 75);
	//オブジェクトの種類に応じて描画
	switch (m_objectname)
	{
		case eType_Box:
		m_box.SetPos(CalcScreenPos());
		m_box.Draw();
		break;

	case eType_Well:
		m_well.SetPos(CalcScreenPos());
		m_well.Draw();
		break;
		 
	case eType_Fence:
		m_fence.SetPos(CalcScreenPos());
		m_fence.Draw();
		break;
	}
	
}
void MapObject::Collision(ObjectBase* b) 
{
	switch (b->m_type)
	{

	case eType_Player:
		if (Player* p = dynamic_cast<Player*>(b))
		{
			if (ObjectBase::CollisionRect(this, p))
			{
				state = 1;
			}
			else
			{
				state = 0;
			}
		}
		break;

	}
}
int MapObject::CollisionPoint(const CVector3D& pos)
{
	//1点のみ検証
	int t = state;
	if (t != 0) return t;
	return 0;
}

int MapObject::CollisionRect(const CVector3D& pos, const CRect& rect)
{
	CRect r = CRect(
		pos.x + rect.m_left,
		pos.y + rect.m_top,
		pos.x + rect.m_right,
		pos.y + rect.m_bottom);
	int t;
	t = CollisionPoint(CVector2D(r.m_left, r.m_top));
	if (t != 0) return t;
	t = CollisionPoint(CVector2D(r.m_right, r.m_top));
	if (t != 0) return t;
	t = CollisionPoint(CVector2D(r.m_left, r.m_bottom));
	if (t != 0) return t;
	t = CollisionPoint(CVector2D(r.m_right, r.m_bottom));
	if (t != 0) return t;
	return 0;
}