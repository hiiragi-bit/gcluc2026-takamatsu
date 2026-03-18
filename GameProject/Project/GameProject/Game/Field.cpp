#include "Field.h"

Field::Field() :ObjectBase(eType_Field)
{
  
    m_forest = COPY_RESOURCE("Field", CImage);
    m_ground = COPY_RESOURCE("Ground", CImage);
   
    
}
void Field::Draw()
{
  
   
   
}
void Field::PreDraw()
{
	
	sc = m_scroll / 16;
	m_forest.SetSize(1920, 1080);
	m_forest.SetRect(sc.x, 0, sc.x + 150, 75);
	m_forest.Draw();

	sc = m_scroll / 8;
	m_ground.SetSize(1920, 1080);
	m_ground.SetRect(sc.x, 0, sc.x + 134, 75);
	m_ground.Draw();
}