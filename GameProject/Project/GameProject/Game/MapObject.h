#pragma once
#include "Base/ObjectBase.h"
class MapObject :public ObjectBase
{
public:
	
public:
	MapObject(char objectname);
	

	void Update() override;
	void Draw() override;
private:
	char m_objectname;
	//CImage m_object;
	//à‰åÀ
	CImage m_well;
	//çÚ
	CImage m_fence;
	//î†
	CImage m_box;
	

};
