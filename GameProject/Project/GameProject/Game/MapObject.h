#pragma once
#include "Base/ObjectBase.h"
#include"Player.h"
#include"Shadow.h"
#include"Map.h"
class MapObject :public ObjectBase
{
public:
	int state;
public:
	MapObject(const CVector3D&pos,char objectname,int objectnb);
	//オブジェクトの種類に応じて画像を変更
	void ChangeObject();

	void Update() ;
	void Draw() ;
	void Collision(ObjectBase* b);
	int CollisionPoint(const CVector3D& pos);
	int CollisionRect(const CVector3D& pos, const CRect& rect);
private:
	char m_objectname;
	int  m_objectnb;
	//CImage m_object;
	//井戸
	CImage m_well;
	//柵
	CImage m_fence;
	//箱
	CImage m_box;
	


};
