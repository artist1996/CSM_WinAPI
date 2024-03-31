#pragma once
#include "CState_Player.h"
class CState_WallKick :
    public CState_Player
{
private:
    bool    m_bAirMove;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CState_WallKick);
    CState_WallKick();
    ~CState_WallKick();
};

