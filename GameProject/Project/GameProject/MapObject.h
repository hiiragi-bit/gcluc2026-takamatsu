#pragma once
#include "Base/ObjectBase.h"
class MapObject :public ObjectBase
{
public:
	MapObject();
	~MapObject();

	
private:
	//à‰åÀ
	CImage m_well[3];
	//çÚ
	CImage m_fence[4];
	//î†
	CImage m_box[5];
	

};
