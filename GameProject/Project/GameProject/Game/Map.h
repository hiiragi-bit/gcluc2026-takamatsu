#pragma once
#include"Base/ObjectBase.h"


class Map : public ObjectBase {
private:
    CImage m_img;
    int state;
   
    
public:
    Map(int area);
    ~Map();
    void Update();
    void Draw();
  
    
  
    
    struct MapData
    {
        
    };
	//マップデータ
    static MapData s_map_data;
  
    
};



