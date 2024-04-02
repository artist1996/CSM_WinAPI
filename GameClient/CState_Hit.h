#pragma once
#include "CState_Player.h"
class CState_Hit :
    public CState_Player
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CState_Hit);
    CState_Hit();
    ~CState_Hit();
};

