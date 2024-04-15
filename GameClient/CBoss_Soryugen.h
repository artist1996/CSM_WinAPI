#pragma once
#include "CState_Boss.h"
class CBoss_Soryugen :
    public CState_Boss
{
private:
    CObj*   m_Soryugen;
    CSound* m_pSound;

    bool    m_Fall;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBoss_Soryugen);
    CBoss_Soryugen();
    virtual ~CBoss_Soryugen();
};

