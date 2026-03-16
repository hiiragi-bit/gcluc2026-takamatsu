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
void Map::PreDraw()
{
	
	m_sky.SetSize(1920, 1080); 
	CVector3D sc(m_scroll / 10);
	m_sky.SetRect(sc.x, 0, sc.x+150,75);
	m_sky.Draw();

	sc = m_scroll / 8;
	m_ground.SetSize(1920, 1080);
	m_ground.SetRect(sc.x, 0, sc.x + 134, 75);
	m_ground.Draw();
	
 }



      

    
