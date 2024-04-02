#pragma once
#include "CState_GigaDeath.h"
class CGigaDeath_Idle :
    public CState_GigaDeath
{
private:
    bool  m_Attack;
    float m_Time;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CGigaDeath_Idle);
    CGigaDeath_Idle();
    virtual ~CGigaDeath_Idle();
};

