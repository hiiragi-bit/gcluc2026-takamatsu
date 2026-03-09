#include "Map.h"

//#include"Goal.h"
Map::MapData Map::s_map_data = {
      
};


  



Map::Map() : ObjectBase(eType_Map)
{

    //âÊëúï°êª
    m_sky = COPY_RESOURCE("Sky", CImage);
	m_ground = COPY_RESOURCE("Ground", CImage);
	m_object = COPY_RESOURCE("Object", CImage);
    
   
    
    
}
Map::~Map() {
  
}
void Map::Update() {
   
}
void Map::Draw()
{
 
	m_sky.SetSize(1920, 1080); 
	m_sky.SetPos(GetScreenPos(m_pos));
	m_sky.Draw();
	m_ground.SetSize(1920, 1080);
	m_ground.SetPos(GetScreenPos(m_pos));
	m_ground.Draw();
	m_object.SetRect(0, 0, 48,48);
	m_object.SetSize(240,240);
	m_object.SetPos(611,620);
	m_object.Draw();
 }



      

    
