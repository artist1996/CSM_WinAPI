#pragma once
#include "CState.h"
class CMonsterIDLE :
    public CState
{
private:


public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CMonsterIDLE);
    CMonsterIDLE();
    ~CMonsterIDLE();
};

