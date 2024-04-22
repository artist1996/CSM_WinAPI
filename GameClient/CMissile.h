#pragma once
#include "CObj.h"

class CForce;

class CMissile :
    public CObj
{
private:
    CObj*       m_Owner;

    CAnimator*  m_Animator;
    CCollider*  m_Collider;

    Vec2        m_CenterPos;

    float       m_Speed;
    float       m_Dir;
    
    float       m_MaxDistance;

public:
    virtual void tick() override;

public:
    CLONE(CMissile);
    CMissile();
    CMissile(Vec2 _Pos, Vec2 _Scale, CObj* _Owner);
    ~CMissile();
};

