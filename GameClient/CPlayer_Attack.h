#pragma once
#include "CObj.h"
class CPlayer_Attack :
    public CObj
{
private:
    CObj*       m_Owner;

    CCollider*  m_Collider;
    CAnimator*  m_Animator;

    ATTACK_TYPE m_eType;
    
private:
    void Attack_01();
    void Attack_02();
    void Attack_03();

public:
    virtual void tick() override;
    void SetAnimator(CAnimator* _Animator) { m_Animator = _Animator; }
    void SetOwner(CObj* _Owner)            { m_Owner = _Owner; }

public:
    CLONE(CPlayer_Attack);
    CPlayer_Attack(CObj* _Owner, Vec2 _Pos, ATTACK_TYPE _Type);
    virtual ~CPlayer_Attack();
};

