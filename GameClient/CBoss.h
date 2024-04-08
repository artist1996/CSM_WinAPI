#pragma once
#include "CObj.h"

class CPlatform;

class CBoss :
    public CObj
{
private:
    CCollider*  m_Collider;
    CRigidBody* m_RigidBody;
    CAnimator*  m_Animator;
    CFSM*       m_FSM;

    CPlatform*  m_Target;
    int         m_HP;

public:
    void SetTarget(CPlatform* _Target) { m_Target = _Target; }

public:
    CLONE(CBoss);
    CBoss();
    CBoss(Vec2 _Pos, int _HP);
    virtual ~CBoss();
};

