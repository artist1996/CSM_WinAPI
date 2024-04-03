#pragma once
#include "CState_Batton.h"
class CBatton_Idle :
    public CState_Batton
{
private:
    float m_Time;

    bool  m_Move;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBatton_Idle);
    CBatton_Idle();
    ~CBatton_Idle();
};