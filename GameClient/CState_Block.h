#pragma once
#include "CState_Player.h"
class CState_Block :
    public CState_Player
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;


public:
    CLONE(CState_Block);
    CState_Block();
    ~CState_Block();
};

