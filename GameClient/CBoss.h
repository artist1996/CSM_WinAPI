#pragma once
#include "CObj.h"

class CPlatform;

class CBoss :
    public CObj
{
private:
    Vec2        m_CenterPos;

    CCollider*  m_Collider;
    CRigidBody* m_RigidBody;
    CAnimator*  m_Animator;
    CFSM*       m_FSM;

    CObj*       m_TargetPlatform;
    int         m_HP;

    float       m_Time;
    
public:
    void SetTarget(CObj* _Target) { m_TargetPlatform = _Target; }

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    CLONE(CBoss);
    CBoss();
    CBoss(Vec2 _Pos, int _HP);
    virtual ~CBoss();

    friend class CUI_Warning;
};

