#pragma once
#include "CState_Boss.h"

class CBoss_Dead :
    public CState_Boss
{
private:
    bool m_First;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBoss_Dead);
    CBoss_Dead();
    virtual ~CBoss_Dead();
};

