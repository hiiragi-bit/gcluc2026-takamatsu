#include "ObjectBase.h"
std::list<ObjectBase*> ObjectBase::m_list;
std::list<ObjectBase*> ObjectBase::m_obj_list;
CVector3D ObjectBase::m_scroll(0, 0, 0);
ObjectBase::ObjectBase(int type, int sort_order) : m_type(type), m_sort_order(sort_order), m_pos(0, 0, 0), m_rad(0), m_kill(false)
{

}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::Update()
{
}

void ObjectBase::PreDraw()
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
    //オブジェクトリストの中身を奥行きの座標が大きい順に並べる
    m_obj_list.sort(
        [](const ObjectBase* task0, const ObjectBase* task1) {
            const ObjectBase* obj0 = dynamic_cast<const ObjectBase*>(task0);
            const ObjectBase* obj1 = dynamic_cast<const ObjectBase*>(task1);
            return obj0->m_pos.z < obj1->m_pos.z;
        }
    );

    //並び変えたオブジェクトリストの先頭から順番に
    //sort_orderの値を設定することでタスクリストの中のオブジェクトの順番にも反映
    int sort_order = 0;
    for (ObjectBase* obj : m_obj_list) {
        obj->SetSortOrder(sort_order);
        sort_order++;
    }
    //リスト内全ての要素の前描画
    for (auto& b : m_list) {
        b->PreDraw();
    }
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

    it = m_obj_list.begin();
    last = m_obj_list.end();
    while (it != last) {
        if ((*it)->m_kill) {
            //オブジェクトリストから除外、次の要素のポインタを受け取る
            it = m_obj_list.erase(it);
        }
        else {
            //次へ
            it++;
        }
    }
}


void ObjectBase::Add(ObjectBase* b, bool sort)
{
    //並び替え時の追加処理でなければ
    if (!sort) {
        //追加されるタスクがオブジェクトなら
        //オブジェクトリストにも登録
        if (eType_Box <= b->m_type && b->m_type <= eType_Magic) {
            m_obj_list.push_back(b);
        }
    }

    auto itr = m_list.begin();
    while (itr != m_list.end()) {
        if ((*itr)->m_sort_order > b->m_sort_order) {
            m_list.insert(itr, b);
            return;
        }
        //Typeが同じ場合は、SortOrder順でソート
        else if (b->m_sort_order == (*itr)->m_sort_order) {
            if (b->m_type < (*itr)->m_type) {
                m_list.insert(itr, b);
                return;
            }
        }
        itr++;
    }

    //リストの末尾へ追加
    m_list.push_back(b);
}

void ObjectBase::Remove(ObjectBase* b, bool sort)
{
    //並び替え時でなければ
    if (!sort) {
        //taskがオブジェクトならオブジェクトリストからも取り除く
        if (eType_Box <= b->m_type && b->m_type <= eType_Magic) {
            m_obj_list.remove(b);
        }
    }
    //オブジェクトをリストから除外
    m_list.remove(b);
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

void ObjectBase::SetSortOrder(int order)
{
    //優先度内の順番が同じなら処理しない
    if (m_sort_order == order) return;
    //優先度内の順番を設定
    m_sort_order = order;
    //一度取り除いて再度追加することで並び変える
    Remove(this, true);
    Add(this, true);
}

CVector2D ObjectBase::GetScreenPos(const CVector3D& pos)
{
    return CVector2D(pos.x - m_scroll.x, pos.y - m_scroll.y);
}

CVector2D ObjectBase::CalcScreenPos(bool grounded) const
{
    CVector2D ret;

    // X座標はそのまま設定
    ret.x = m_pos.x;
    // 通常座標を求める場合
    if (!grounded)
    {
        // Y座標は、3次元座標のY（高さ）とZ（奥行）を合わせる
        float posZ = FIELD_CENTER_Z + m_pos.z;
        ret.y = -m_pos.y + posZ;
    }
    // 高さを考慮しない地面の位置を求める場合
    else
    {
        // Y座標は、3次元座標のZ（奥行）のみ反映する
        ret.y = FIELD_CENTER_Z + m_pos.z;
    }

    return ret;
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
