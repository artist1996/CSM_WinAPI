#pragma once
#include "CState_Mettool.h"
class CMettool_Patrol :
    public CState_Mettool
{
private:
    float m_Dir;
    float m_Speed;

    float m_ShootTime;

    bool  m_Attack;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CMettool_Patrol();
    ~CMettool_Patrol();
};

