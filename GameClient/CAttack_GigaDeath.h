#pragma once
#include "CObj.h"
class CAttack_GigaDeath :
    public CObj
{
private:
    CCollider* m_Collider;
    CAnimator* m_Animator;
    
    Vec2       m_CenterPos;

    float      m_Speed;
    float      m_MaxDistance;

public:
    virtual void tick() override;

public:
    CLONE(CAttack_GigaDeath);
    CAttack_GigaDeath();
    CAttack_GigaDeath(Vec2 _Pos, Vec2 _Scale);
    ~CAttack_GigaDeath();
};