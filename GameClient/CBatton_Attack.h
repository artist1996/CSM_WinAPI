#pragma once
#include "CState_Batton.h"
class CBatton_Attack :
    public CState_Batton
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBatton_Attack);
    CBatton_Attack();
    ~CBatton_Attack();
};

