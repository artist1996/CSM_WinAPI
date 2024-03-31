#pragma once
#include "CState_Player.h"
class CState_Jump :
    public CState_Player
{
private:
    float   m_Speed;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CState_Jump();
    ~CState_Jump();
};

