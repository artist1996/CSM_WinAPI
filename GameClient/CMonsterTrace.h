#pragma once
#include "CState.h"
class CMonsterTrace :
    public CState
{
private:
    
    
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CMonsterTrace);
    CMonsterTrace();
    ~CMonsterTrace();
};

