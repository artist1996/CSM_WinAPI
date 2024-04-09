#pragma once
#include "CState_Boss.h"

class CBoss_Hadouken :
    public CState_Boss
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBoss_Hadouken);
    CBoss_Hadouken();
    virtual ~CBoss_Hadouken();
};

