#pragma once
#include "CState_GigaDeath.h"
class CGigaDeath_Attack :
    public CState_GigaDeath
{
private:
    int m_Count;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CGigaDeath_Attack);
    CGigaDeath_Attack();
    virtual ~CGigaDeath_Attack();
};

