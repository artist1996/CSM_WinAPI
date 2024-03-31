#pragma once
#include "CState_Player.h"
class CState_WallEnter :
    public CState_Player
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CState_WallEnter();
    ~CState_WallEnter();

};