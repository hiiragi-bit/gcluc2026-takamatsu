#pragma once
#include"Base/ObjectBase.h"
#include"Game/Swordsman.h"

class Map : public ObjectBase {
private:
    CImage m_sky;
	CImage m_ground;
    CImage m_house;
    CImage m_house2;
    int state;
	
    CVector3D sc;
    
    
public:
    Map();
    ~Map();
    void Update();
    void PreDraw();
	
  
    
    struct MapData
    {
        
    };
	//マップデータ
    static MapData s_map_data;
  
    
};



