#pragma once
#include "CState_Boss.h"
class CBoss_Enter :
    public CState_Boss
{
private:
    CSound* m_pBGM;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBoss_Enter);
    CBoss_Enter();
    virtual ~CBoss_Enter();
};

