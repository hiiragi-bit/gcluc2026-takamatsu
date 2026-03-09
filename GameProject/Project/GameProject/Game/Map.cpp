#include "Map.h"

//#include"Goal.h"
Map::MapData Map::s_map_data = {
      
};


  



Map::Map() : ObjectBase(eType_Map)
{

    //âÊëúï°êª
    m_sky = COPY_RESOURCE("Sky", CImage);
	m_ground = COPY_RESOURCE("Ground", CImage);
	
    
}
Map::~Map() {
  
}
void Map::Update() 
{
   
}
void Map::Draw()
{
 
	m_sky.SetSize(1920, 1080); 
	m_sky.SetPos(GetScreenPos(m_pos));
	m_sky.Draw();
	m_ground.SetSize(1920, 1080);
	m_ground.SetPos(GetScreenPos(m_pos));
	m_ground.Draw();
	
 }



      

    
