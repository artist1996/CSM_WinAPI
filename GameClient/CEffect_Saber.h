#pragma once
#include "CObj.h"

class CEffect_Saber :
    public CObj
{
private:
    CAnimator*  m_Animator;
    EFFECT_TYPE m_Type;
    
public:
    virtual void tick();

public:
    CLONE(CEffect_Saber);
    CEffect_Saber();
    CEffect_Saber(Vec2 _Pos, EFFECT_TYPE _Type);
    ~CEffect_Saber();
};

