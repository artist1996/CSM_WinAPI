#pragma once
#include "CMonster.h"
class CMonster_Raiden :
    public CMonster
{
private:
    CAnimator* m_Animator;
    CCollider* m_Collider;
    CRigidBody* m_RigidBody;
    CFSM* m_FSM;

public:
    virtual void begin() override;
        
public:
    CLONE(CMonster_Raiden);
    CMonster_Raiden();
    CMonster_Raiden(Vec2 _Pos, Vec2 _Scale, int _HP, float _DetectRange);
    ~CMonster_Raiden();
};

