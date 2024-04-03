#pragma once
#include "CTrap.h"

class CTrap_Meteor :
    public CTrap
{
private:
    CRigidBody* m_RigidBody;
    CCollider*  m_Collider;
    CAnimator*  m_Animator;

public:
    virtual void tick() override;

public:
    CLONE(CTrap_Meteor);
    CTrap_Meteor();
    CTrap_Meteor(Vec2 _Pos, OBJ_ID _ID);
    virtual ~CTrap_Meteor();
};

