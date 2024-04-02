#pragma once
#include "CState_Mettool.h"
class CMettool_Idle :
    public CState_Mettool
{
private:
    float m_Time;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CMettool_Idle();
    ~CMettool_Idle();
};