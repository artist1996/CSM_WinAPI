#pragma once
#include "CTrap.h"

class CTrap_Meteor :
    public CTrap
{
private:
    CRigidBody* m_RigidBody;
    CCollider*  m_Collider;
    CAnimator*  m_Animator;

    int         m_HP;
    float       m_Time;
   // PLAYER_JUMPATTACK
public:
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    CLONE(CTrap_Meteor);
    CTrap_Meteor();
    CTrap_Meteor(Vec2 _Pos, OBJ_ID _ID);
    virtual ~CTrap_Meteor();
};

