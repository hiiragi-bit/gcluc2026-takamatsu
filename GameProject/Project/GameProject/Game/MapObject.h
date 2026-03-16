#pragma once
#include "Base/ObjectBase.h"
#include"Player.h"
class MapObject :public ObjectBase
{
public:
	
public:
	MapObject(const CVector3D&pos,char objectname,int objectnb);
	//オブジェクトの種類に応じて画像を変更
	void ChangeObject();

	void Update() ;
	void Draw() ;
	void Collision(ObjectBase* b);
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
