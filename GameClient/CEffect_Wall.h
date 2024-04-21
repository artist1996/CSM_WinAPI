#pragma once
#include "CObj.h"
class CEffect_Wall :
    public CObj
{
private:
    CObj*       m_Owner;

    CRigidBody* m_RigidBody;
    CAnimator*  m_Animator;

public:
    virtual void tick() override;

public:
    CLONE(CEffect_Wall);
    CEffect_Wall(CObj* _Owner, CRigidBody* _RigidBody);
    virtual ~CEffect_Wall();
};

