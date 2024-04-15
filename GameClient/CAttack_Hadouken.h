#pragma once
#include "CObj.h"
class CAttack_Hadouken :
    public CObj
{
private:
    CObj*      m_Owner;

    CCollider* m_Collider;
    CAnimator* m_Animator;

public:
    virtual void tick() override;

    
public:
    CLONE(CAttack_Hadouken);
    CAttack_Hadouken();
    CAttack_Hadouken(CObj* _Owner, Vec2 _Pos);
    virtual ~CAttack_Hadouken();
};

