#include "MapObject.h"
#include <vector>
#include <string>

// MapObject コンストラクタ
MapObject::MapObject(char objectname) : ObjectBase(objectname)
{
	m_box = COPY_RESOURCE("Box", CImage);

}

void MapObject::Update() {

}
void MapObject::Draw() {

}