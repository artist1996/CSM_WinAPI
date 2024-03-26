#pragma once
#include "CObj.h"
class CLine :
    public CObj
{
private:
    CCollider*      m_Collider;

public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    CLONE(CLine)
    CLine();
    CLine(Vec2 _StartPos, Vec2 _EndPos);
    ~CLine();
};