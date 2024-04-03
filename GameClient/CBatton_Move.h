#pragma once
#include "CState_Batton.h"
class CBatton_Move :
    public CState_Batton
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBatton_Move);
    CBatton_Move();
    ~CBatton_Move();
};

