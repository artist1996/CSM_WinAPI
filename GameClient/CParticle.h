#pragma once
#include "CObj.h"
class CParticle :
    public CObj
{
private:
    CObj*       m_Owner;
    CAnimator*  m_Animator;

    EFFECT_TYPE m_Type;

    bool        m_Active;

public:
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CParticle);
    CParticle();
    CParticle(EFFECT_TYPE _Type);
    virtual ~CParticle();
};

