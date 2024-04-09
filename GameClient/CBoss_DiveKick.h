#pragma once
#include "CState_Boss.h"
class CBoss_DiveKick :
    public CState_Boss
{
private:
    CObj* m_DiveKick;

    Vec2  m_CenterPos;
    Vec2  m_Dir;

    bool  m_bUP;
    bool  m_bDown;
    bool  m_bFirst;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBoss_DiveKick);
    CBoss_DiveKick();
    virtual ~CBoss_DiveKick();
};

