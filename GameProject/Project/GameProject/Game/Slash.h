#pragma once
#include "Base/ObjectBase.h"

//éaåÇÇÃó^É_ÉÅÅ[ÉW
#define SLASH_DAMAGE 1

class Slash :public ObjectBase {
private:
	//CImage m_img;
	int m_attackNo;
	int m_cnt;			//âº
	bool m_flip;
public:
	Slash(const CVector3D& pos, int attack_no, int type, bool flip);
	~Slash();
	void Update() override;
	void Draw() override;
	void Collision(ObjectBase* o);
};