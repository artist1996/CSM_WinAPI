#pragma once
#include "CState_Player.h"
class CState_Attack02 :
    public CState_Player
{
private:
    CSound* m_pSound;
    bool    m_bNext;
    

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CState_Attack02);
    CState_Attack02();
    ~CState_Attack02();
};

