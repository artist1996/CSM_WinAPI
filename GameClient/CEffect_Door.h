#pragma once
#include "CObj.h"
class CEffect_Door :
    public CObj
{
private:
    CAnimator* m_Animator;

public:
    virtual void tick() override;

public:
    CLONE(CEffect_Door);
    CEffect_Door();
    CEffect_Door(Vec2 _Pos);
    ~CEffect_Door();
};

