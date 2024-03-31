#pragma once
#include "CState_Player.h"


class CState_Attack01 :
    public CState_Player
{
private:
    bool m_bNext;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CState_Attack01);
    CState_Attack01();
    ~CState_Attack01();
};

