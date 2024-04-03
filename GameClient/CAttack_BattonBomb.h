#pragma once
#include "CObj.h"
class CAttack_BattonBomb :
    public CObj
{
private:
    CObj*       m_Owner;
    CCollider*  m_Collider;
    CAnimator*  m_Animator;
    
    bool        m_bActive;

    bool        m_bPlay;
    bool        m_bCurPlay;
    
public:
    virtual void tick() override;

public:
    CLONE(CAttack_BattonBomb);
    CAttack_BattonBomb();
    CAttack_BattonBomb(CObj* _Owner, bool _Active);
    ~CAttack_BattonBomb();
};

