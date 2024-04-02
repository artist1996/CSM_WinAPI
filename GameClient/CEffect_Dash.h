#pragma once
#include "CObj.h"
class CEffect_Dash :
    public CObj
{
private:
    CObj* m_Owner;

    CAnimator* m_Animator;

public:
    virtual void tick() override;

public:
    CLONE(CEffect_Dash);
    CEffect_Dash(CObj* _Owner, Vec2 _Pos, Vec2 _Scale);
    ~CEffect_Dash();
};

