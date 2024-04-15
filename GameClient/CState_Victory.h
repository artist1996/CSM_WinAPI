#pragma once
#include "CState_Player.h"
class CState_Victory :
    public CState_Player
{
private:
    CAnimator* m_Animator;

    CSound*    m_VictorySound;
    CSound*    m_RecallSound;

    Vec2 m_CenterPos;

    float m_Time;

    bool m_bAnimation;
    bool m_Play;
    bool m_bUP;

    bool m_Victory;
    bool m_Recall;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CState_Victory);
    CState_Victory();
    virtual ~CState_Victory();
};

