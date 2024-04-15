#pragma once
#include "CObj.h"
class CAttack_Breath :
    public CObj
{
private:
    CObj*      m_Owner;

    CCollider* m_Collider;
    CAnimator* m_Animator;

    Vec2       m_CenterPos;
    float      m_Dir;

    bool       m_Play;

public:
    virtual void tick() override;

public:
    CLONE(CAttack_Breath);
    CAttack_Breath();
    CAttack_Breath(CObj* _Owner);
    virtual ~CAttack_Breath();
};

