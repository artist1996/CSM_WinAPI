#pragma once
#include "CObj.h"

class CAttack_Raiden :
    public CObj
{
private:
    CObj*      m_Owner;

    CCollider* m_Collider;
    CAnimator* m_Animator;

public:
    virtual void tick() override;

private:
    void Attack();

public:
    CLONE(CAttack_Raiden);
    CAttack_Raiden();
    CAttack_Raiden(CObj* _Owner, CAnimator* _Animator);
    virtual ~CAttack_Raiden();

};

