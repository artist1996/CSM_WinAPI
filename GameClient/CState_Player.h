#pragma once
#include "CState.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

class CRigidBody;
class CAnimator;
class CCollider;

class CState_Player :
    public CState
{
private:
    CRigidBody* m_Rigidbody;
    CAnimator*  m_Animator;
    CCollider*  m_Collider;

protected:
    CRigidBody* GetRigidBody() { return m_Rigidbody; }
    CAnimator* GetAnimator()   { return m_Animator; }
    CCollider* GetCollider()   { return m_Collider; }

public:
    void Initialize()
    {
        if (nullptr == m_Rigidbody && nullptr == m_Animator && nullptr == m_Collider)
        {
            m_Rigidbody = GetObj()->GetComponent<CRigidBody>();
            m_Animator = GetObj()->GetComponent<CAnimator>();
            m_Collider = GetObj()->GetComponent<CCollider>();
        }
    }

    void Play(const wstring& _strName) { m_Animator->Play(_strName, false); }
    virtual void Enter() PURE;
    virtual void FinalTick() PURE;
    virtual void Exit() PURE;

public:
    CLONE_DISABLE(CState_Player);
    CState_Player();
    ~CState_Player();
};

