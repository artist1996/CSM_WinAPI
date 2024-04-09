#pragma once
#include "CObj.h"
class CAttack_DiveKick :
    public CObj
{
private:
    CObj*      m_Owner;

    CCollider* m_Collider;
    CAnimator* m_Animator;

    
public:
    virtual void tick() override;

public:
    CLONE(CAttack_DiveKick);
    CAttack_DiveKick();
    CAttack_DiveKick(CObj* _Owner);
    virtual ~CAttack_DiveKick();
};

