#pragma once
#include "CState_Boss.h"
class CBoss_Breath :
    public CState_Boss
{
private:
    int   m_Count;

    float m_Time;
    float m_Dir;

    bool  m_Animation;
    bool  m_Attack;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBoss_Breath);
    CBoss_Breath();
    virtual ~CBoss_Breath();
};

