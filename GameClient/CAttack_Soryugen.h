#pragma once
#include "CObj.h"
class CAttack_Soryugen :
    public CObj
{
private:
    CObj* m_Owner;

    CCollider* m_Collider;
    CAnimator* m_Animator;

public:
    virtual void tick() override;

public:
    CLONE(CAttack_Soryugen);
    CAttack_Soryugen();
    CAttack_Soryugen(CObj* _Owner);
    virtual ~CAttack_Soryugen();
};