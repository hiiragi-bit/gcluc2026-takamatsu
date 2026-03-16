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
			m_box.SetCenter(120, 120);
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
		m_well.SetCenter(160,160);
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
		m_fence.SetCenter(120, 120);
		
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
		m_box.SetPos(GetScreenPos(m_pos));
		m_box.Draw();
		DrawRect();
		break;

	case eType_Well:
		m_well.SetPos(GetScreenPos(m_pos));
		m_well.Draw();
		break;
		 
	case eType_Fence:
		m_fence.SetPos(GetScreenPos(m_pos));
		m_fence.Draw();
		break;
	}
	
}
void MapObject::Collision(ObjectBase* b) 
{
	
	
}