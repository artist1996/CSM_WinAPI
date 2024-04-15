#pragma once
#include "CState_Player.h"
class CState_Attack03 :
    public CState_Player
{
private:
    CSound* m_pSound;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CState_Attack03);
    CState_Attack03();
    ~CState_Attack03();
};

