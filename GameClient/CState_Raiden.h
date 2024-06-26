#pragma once
#include "CState.h"

#include "CAnimator.h"

class CState_Raiden :
    public CState
{
private:
    CAnimator* m_Animator;

protected:
    void Initialize()
    {
        if (nullptr == m_Animator)
        {
            m_Animator = GetObj()->GetComponent<CAnimator>();
        }
    }

    CAnimator* GetAnimator() { return m_Animator; }

public:
    virtual void Enter() PURE;
    virtual void FinalTick() PURE;
    virtual void Exit() PURE;


public:
    CState_Raiden();
    virtual ~CState_Raiden();
};

