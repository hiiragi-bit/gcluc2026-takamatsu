#include "ObjectBase.h"
std::list<ObjectBase*> ObjectBase::m_list;
CVector3D ObjectBase::m_scroll(0, 0, 0);
ObjectBase::ObjectBase(int type) : m_type(type), m_pos(0, 0, 0), m_rad(0), m_kill(false)
{

}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::Update()
{
}

void ObjectBase::Draw()
{
}
void ObjectBase::Collision(ObjectBase* b)
{
}
bool ObjectBase::CollisionCircle(ObjectBase* b1, ObjectBase* b2)
{
    CVector3D v = b1->m_pos - b2->m_pos;
    float l = v.Length();
    if (l < b1->m_rad + b2->m_rad) {
        return true;
    }
    return false;
}
void ObjectBase::CollisionAll()
{
    auto it1 = m_list.begin();
    auto last = m_list.end();
    while (it1 != last) {
        auto it2 = it1;
        it2++;
        while (it2 != last) {
            (*it1)->Collision(*it2);
            (*it2)->Collision(*it1);
            it2++;
        }
        it1++;
    }
}


void ObjectBase::UpdateAll()
{
    //リスト内全ての要素の更新
    for (auto& b : m_list) {
        b->Update();
    }
}

void ObjectBase::DrawAll()
{
    //リスト内全ての要素の描画
    for (auto& b : m_list) {
        b->Draw();
    }
}

void ObjectBase::CheckKillAll()
{
    auto it = m_list.begin();
    auto last = m_list.end();
    while (it != last) {
        if ((*it)->m_kill) {
            delete (*it);
            //リストから除外、次の要素のポインタを受け取る
            it = m_list.erase(it);
        }
        else {
            //次へ
            it++;
        }
    }
}


void ObjectBase::Add(ObjectBase* b)
{
    //Type順によるソート
    auto itr = m_list.begin();
    while (itr != m_list.end()) {
        if ((*itr)->m_type > b->m_type) {
            m_list.insert(itr, b);
            return;
        }
        itr++;
    }
    //リストの末尾へ追加
    m_list.push_back(b);
}
void ObjectBase::KillAll()
{
    for (auto& b : m_list) {
        b->SetKill();
    }
}

void ObjectBase::Kill(int mask)
{
    for (auto& b : m_list) {
        if ((1 << b->m_type) & (mask))
            b->SetKill();
    }
}

ObjectBase* ObjectBase::FindObject(int type)
{
    //リストをループ
    for (auto& b : m_list) {
        //対象のオブジェクトを見つけたら、それを返す
        if (b->m_type == type)
            return b;
    }
    return nullptr;

}

std::list<ObjectBase*> ObjectBase::FindObjects(int type)
{
    std::list<ObjectBase*> ret;
    //リストをループ
    for (auto& b : m_list) {
        //対象のオブジェクトを見つけたら、返却用リストに追加
        if (b->m_type == type)
            ret.push_back(b);
    }
    return ret;
}

CVector2D ObjectBase::GetScreenPos(const CVector3D& pos)
{
    return CVector2D(pos.x - m_scroll.x, pos.y - m_scroll.y);
}
void ObjectBase::DrawRect()
{
    //デバッグ用　矩形の表示
    CRect rect = CRect(
        m_pos.x + m_rect.m_left,
        m_pos.y + m_rect.m_top,
        m_pos.x + m_rect.m_right,
        m_pos.y + m_rect.m_bottom);
    Utility::DrawQuad(
        CVector2D(rect.m_left, rect.m_top) - CVector2D(m_scroll.x, m_scroll.y),
        CVector2D(rect.m_width, rect.m_height),
        CVector4D(1, 0, 0, 0.5f));
}



bool ObjectBase::CollisionRect(ObjectBase* b1, ObjectBase* b2)
{
    //b1の矩形
    CRect rect1 = CRect(
        b1->m_pos.x + b1->m_rect.m_left,
        b1->m_pos.y + b1->m_rect.m_top,
        b1->m_pos.x + b1->m_rect.m_right,
        b1->m_pos.y + b1->m_rect.m_bottom);
    //b2の矩形
    CRect rect2 = CRect(
        b2->m_pos.x + b2->m_rect.m_left,
        b2->m_pos.y + b2->m_rect.m_top,
        b2->m_pos.x + b2->m_rect.m_right,
        b2->m_pos.y + b2->m_rect.m_bottom);

    //矩形同士の判定
    if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
        rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
        return true;

    return false;
}
