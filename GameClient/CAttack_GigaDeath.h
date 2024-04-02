#pragma once
#include "CObj.h"
class CAttack_GigaDeath :
    public CObj
{
private:
    CAnimator* m_Animator;

    Vec2 m_CenterPos;


public:

public:
    CAttack_GigaDeath();
    ~CAttack_GigaDeath();
};