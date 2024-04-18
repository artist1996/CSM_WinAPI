#pragma once
#include "CState_Player.h"
class CState_Dead :
    public CState_Player
{
private:
    CSound* m_pSound;

    float   m_Time;
    float   m_ChangeStateTime;
    float   m_FadeTime;

    bool    m_Dead;
    bool    m_First;
    bool    m_CamEvent;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CState_Dead);
    CState_Dead();
    virtual ~CState_Dead();

};

