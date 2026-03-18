#pragma once
#include"Base/ObjectBase.h"

class Field : public ObjectBase {
private:
   
    //画像オブジェクト（遠景）
    CImage m_forest;
    //画像オブジェクト（最遠景）
    CImage m_ground;
	CVector3D sc;
  
  

public:
    /// コンストラクタ
    Field();
    /// 描画
    void Draw();
	void PreDraw();
    };