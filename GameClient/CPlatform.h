#pragma once
#include "CObj.h"
class CPlatform :
    public CObj
{
private:
    CCollider* m_Collider;

public:
    virtual void tick() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

    CLONE(CPlatform)
public:
    CPlatform();
    CPlatform(Vec2 _Pos, Vec2 _Scale, LAYER_TYPE _type);
    ~CPlatform();
};

