#pragma once
#include "CObj.h"
class CPlatform_Level :
    public CObj
{
private:
    CCollider* m_Collider;

public:
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    CLONE(CPlatform_Level);
    CPlatform_Level();
    CPlatform_Level(Vec2 _Pos);
    virtual ~CPlatform_Level();
};

