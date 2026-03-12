#pragma once
//Z軸の中心(0の場所)
#define FIELD_CENTER_Z (SCREEN_HEIGHT * 0.75f)
//Zの下限(奥)
#define MIN_Z -230.0f
//Zの上限(手前)
#define MAX_Z 280.0f


/// <summary>
/// オブジェクトの種類
/// </summary>
enum {
    eType_Title,
    eType_Map,
    eType_Shadow,
	eType_Box,
    eType_Fence,
	eType_Well,
    eType_Player,
    eType_Witch,
    eType_Swordsman,
    eType_Hero,
    eType_Magic,
    eType_Effect,
    eType_Scene,
    eType_UI,
};
//重力加速度
#define GRAVITY -1.0f

/// <summary>
/// ゲームオブジェクトの基底クラス
/// </summary>
class ObjectBase {
public:
    //オブジェクトの種類
    int m_type;
    //オブジェクトの優先度
    int m_sort_order;
    //座標データ
    CVector3D m_pos;
    //過去の位置
    CVector3D m_pos_old;
    //半径
    float m_rad;
    //移動ベクトル
    CVector3D m_vec;

    //回転ベクトル
    CVector3D m_rot;

    //矩形
    CRect   m_rect;
    bool m_kill;
    static std::list<ObjectBase*> m_list;
    static std::list<ObjectBase*> m_obj_list;
    //スクロール値
    static CVector3D m_scroll;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ObjectBase(int type, int sort_order = 0);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ObjectBase();
    /// <summary>
    /// 更新処理
    /// </summary>
    virtual void Update();
    /// <summary>
   /// 前描画処理
   /// </summary>
    virtual void PreDraw();
    /// <summary>
    /// 描画処理
    /// </summary>
    virtual void Draw();
    /// <summary>
    /// オブジェクト削除
    /// </summary>
    void SetKill() { m_kill = true; }

    virtual void Collision(ObjectBase* b);
    /// <summary>
    /// 円同士の当たり判定
    /// </summary>
    /// <param name="b1">対象1</param>
    /// <param name="b2">対象2</param>
    /// <returns></returns>
    static bool CollisionCircle(ObjectBase* b1, ObjectBase* b2);


    /// <summary>
    /// 全てのオブジェクトの更新
    /// </summary>
    static void UpdateAll();
    /// <summary>
    /// 全てのオブジェクトの描画
    /// </summary>
    static void DrawAll();
    /// <summary>
    /// 全てのオブジェクト同士の組み合わせで当たり判定検証
    /// </summary>
    static void CollisionAll();
    /// <summary>
    /// 全てのオブジェクトの削除チェック
    /// </summary>
    static void CheckKillAll();

    /// <summary>
    /// オブジェクトをリストへ追加
    /// </summary>
    /// <param name="b">追加オブジェクト</param>
    static void Add(ObjectBase* b, bool sort = false);
    /// <summary>
    /// オブジェクトをリストから除外
    /// </summary>
    /// <param name="b">除外オブジェクト</param>
    static void Remove(ObjectBase* b, bool sort = false);

    /// <summary>
    /// 全オブジェクトの削除
    /// </summary>
    static void KillAll();
    /// <summary>
    /// 指定オブジェクトの削除
    /// </summary>
    /// <param name="mask">削除対象オブジェクトのマスク</param>
    static void Kill(int mask);

    /// <summary>
    /// リスト内からオブジェクトを探索
    /// </summary>
    /// <param name="type">種類</param>
    /// <returns>最初に見つけたオブジェクト</returns>
    static ObjectBase* FindObject(int type);
    /// <summary>
    /// リスト内からオブジェクトを探索
    /// </summary>
    /// <param name="type">種類</param>
    /// <returns>該当種類のオブジェクトのリスト</returns>
    static std::list<ObjectBase*> FindObjects(int type);

    /// <summary>
    /// オブジェクトの優先度を設定
    /// </summary>
    /// <param name="order">設定する優先度</param>
    void SetSortOrder(int order);

    /// <summary>
    /// 画面内での位置を取得
    /// </summary>
    /// <param name="pos">キャラクターなどの座標</param>
    /// <returns>画面上での位置</returns>
    static CVector2D GetScreenPos(const CVector3D& pos);
    /// <summary>
    /// 3次元座標からスクリーン座標（2D）に変換
    /// </summary>
    /// <param name="grounded">trueならば、高さは考慮せず地面の位置を返す</param>
    /// <returns>スクリーン座標</returns>
    CVector2D CalcScreenPos(bool grounded = false) const;

    /// <summary>
    /// 矩形同士の判定
    /// </summary>
    /// <param name="b1">対象</param>
    /// <param name="b2">対象</param>
    /// <returns></returns>
    static bool CollisionRect(ObjectBase* b1, ObjectBase* b2);
    /// <summary>
    /// 矩形の表示
    /// </summary>
    void DrawRect();


};
