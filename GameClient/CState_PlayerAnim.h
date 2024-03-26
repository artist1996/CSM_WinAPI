#pragma once
#include "CState.h"

class CAnimator;

class CState_PlayerAnim :
    public CState
{
private:
    CAnimator*   m_Animator;



public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

private:
    void Idle();
    void Idle_Heart();
    void Hit();
    void Move();
    void Jump();
    void Dash();
    void Attack();
    void Fall();
    void Wall();
    void WallKick();
    void Fire();
    void Ice();
    void GigaAttack();

public:
    CLONE(CState_PlayerAnim);
    CState_PlayerAnim();
    ~CState_PlayerAnim();

};

