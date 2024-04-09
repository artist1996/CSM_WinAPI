#pragma once
#include "CObj.h"

class CPlatform :
    public CObj
{
private:
    CCollider*    m_Collider;
    bool          m_Boss;

public:
    virtual void begin() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    
public:
    CLONE(CPlatform);
    CPlatform();
    CPlatform(const Vec2& _StartPos, const Vec2& _EndPos);
    CPlatform(Vec2 _Pos, Vec2 _Scale, LAYER_TYPE _type);
    ~CPlatform();
};

