#pragma once
#include "CState_Mettool.h"
class CMettool_Attack :
    public CState_Mettool
{
private:
    float m_ShootTime;
    
    bool  m_Change;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CMettool_Attack();
    virtual ~CMettool_Attack();
};

