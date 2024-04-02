#pragma once
#include "CState_Raiden.h"
class CRaiden_StandBy :
    public CState_Raiden
{
private:
    float m_Time;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CRaiden_StandBy);
    CRaiden_StandBy();
    virtual ~CRaiden_StandBy();
};

