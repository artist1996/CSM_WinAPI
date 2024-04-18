#pragma once
#include "CObj.h"
class CPlatform_Death :
    public CObj
{
private:
    CCollider* m_Collider;
    float      m_Range;
    OBJ_ID     m_ID;

public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    float GetRange() { return m_Range; }

public:
    CLONE(CPlatform_Death);
    CPlatform_Death();
    CPlatform_Death(Vec2 _Pos, Vec2 _Scale);
    virtual ~CPlatform_Death();
};

