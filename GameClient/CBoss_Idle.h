#pragma once
#include "CState_Boss.h"
class CBoss_Idle :
    public CState_Boss
{
private:
    int     m_Rand;

    float   m_Dir;
    float   m_Time;
    float   m_CurDir;

    bool    m_Count;
    bool    m_bEncounter;
    bool    m_Attack;

    bool    m_bBreath;
    
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBoss_Idle);
    CBoss_Idle();
    ~CBoss_Idle();
};

