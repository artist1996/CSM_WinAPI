#pragma once
#include "CMonster.h"
class CMonster_GigaDeath :
    public CMonster
{
private:
    CRigidBody* m_RigidBody;
    CCollider*  m_Collider;
    CAnimator*  m_Animator;
    CFSM*       m_FSM;

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(CMonster_GigaDeath);
    CMonster_GigaDeath();
    CMonster_GigaDeath(Vec2 _Pos, Vec2 _Scale, int _HP, float _DetectRange);
    ~CMonster_GigaDeath();
};