#pragma once
#include "CState_Player.h"
class CState_Dash :
    public CState_Player
{
private:
    CSound* m_pSound;
    bool    m_bSound;
    bool    m_AfterImg;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CState_Dash);
    CState_Dash();
    ~CState_Dash();
};

