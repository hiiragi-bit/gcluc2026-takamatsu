#pragma once
#include"Base/ObjectBase.h"


class Map : public ObjectBase {
private:
    CImage m_sky;
	CImage m_ground;
    int state;
   
    
public:
    Map();
    ~Map();
    void Update();
    void Draw();
  
    
  
    
    struct MapData
    {
        
    };
	//マップデータ
    static MapData s_map_data;
  
    
};



