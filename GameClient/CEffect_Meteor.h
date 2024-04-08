#pragma once
#include "CObj.h"

class CEffect_Meteor :
    public CObj
{
private:
    CTexture*     m_Img;
    CRigidBody*   m_RigidBody;
    
    METEOR_EFFECT m_Type;

    float         m_Time;

public:
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CEffect_Meteor);
    CEffect_Meteor();
    CEffect_Meteor(Vec2 _Pos, METEOR_EFFECT _Type);
    virtual ~CEffect_Meteor();
};

