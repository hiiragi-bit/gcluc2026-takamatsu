#include "Map.h"

//#include"Goal.h"
Map::MapData Map::s_map_data = {
      
};


  



Map::Map() : ObjectBase(eType_Map)
{

    //âÊëúï°êª
    m_sky = COPY_RESOURCE("Sky", CImage);
	m_ground = COPY_RESOURCE("Ground", CImage);
	m_house = COPY_RESOURCE("Hause", CImage);
	
    
} 
Map::~Map() {
  
}
void Map::Update() 
{
	
		
	
}
void Map::PreDraw()
{
	
	sc = m_scroll / 16;
	m_sky.SetSize(1920, 1080); 
	m_sky.SetRect(sc.x, 0, sc.x+150,75);
	m_sky.Draw();

	sc = m_scroll / 8;
	m_ground.SetSize(1920, 1080);
	m_ground.SetRect(sc.x, 0, sc.x + 134, 75);
	m_ground.Draw();

	sc = m_scroll / 19;
	m_house.SetSize(1920,460);
	m_house.SetPos(0, 150);
	m_house.SetRect(sc.x, 0, sc.x + 134, 46);
	m_house.Draw();
	
 }

	

      

    
