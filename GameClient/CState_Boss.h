#pragma once
#include "CState.h"

#include "CAnimator.h"
#include "CRigidBody.h"

class CPlatform;

class CState_Boss :
    public CState
{
private:
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;
    
    CPlatform*  m_Target;

public:
    void Initialize()
    {
        if (nullptr == m_Animator && nullptr == m_RigidBody)
        {
            m_Animator = GetObj()->GetComponent<CAnimator>();
            m_RigidBody = GetObj()->GetComponent<CRigidBody>();
        }
    }

    CAnimator* GetAnimator()   { return m_Animator; }
    CRigidBody* GetRigidBody() { return m_RigidBody; }

    void SetTarget(CPlatform* _Target) { m_Target = _Target; }
    
public:
    virtual void Enter() PURE;
    virtual void FinalTick() PURE;
    virtual void Exit() PURE;

public:
    CState_Boss();
    virtual ~CState_Boss();
};

