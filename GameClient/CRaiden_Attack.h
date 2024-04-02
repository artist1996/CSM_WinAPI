#pragma once
#include "CState_Raiden.h"

class CRaiden_Attack :
    public CState_Raiden
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CRaiden_Attack);
    CRaiden_Attack();
    virtual ~CRaiden_Attack();
};

