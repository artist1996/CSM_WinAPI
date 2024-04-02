#pragma once
#include "CMonster.h"
class CMonster_Mettool :
    public CMonster
{
private:
    CAnimator*  m_Animator;
    CCollider*  m_Collider;
    CRigidBody* m_RigidBody;
    CFSM*       m_FSM;

    Vec2        m_vCenterPos;

    float       m_MaxDistance;

private:
    void Shoot();

public:
    virtual void begin() override;

public:
    CLONE(CMonster_Mettool);
    CMonster_Mettool(Vec2 _Pos, Vec2 _Scale, int _HP ,float _DetectRange);
    ~CMonster_Mettool();
};

