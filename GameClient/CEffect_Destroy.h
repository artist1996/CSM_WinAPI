#pragma once
#include "CObj.h"

class CAnimator;

class CEffect_Destroy :
    public CObj
{
private:
    CObj*      m_Owner;
    CAnimator* m_Animator;

public:
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CEffect_Destroy);
    CEffect_Destroy();
    CEffect_Destroy(CObj* _Owner);
    virtual ~CEffect_Destroy();
};

