#pragma once
#include "CState_Raiden.h"
class CRaiden_Idle :
    public CState_Raiden
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CRaiden_Idle);
    CRaiden_Idle();
    virtual ~CRaiden_Idle();
};

