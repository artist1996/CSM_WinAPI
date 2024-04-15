#pragma once
#include "CObj.h"
class CEffect_MonsterDead :
    public CObj
{
private:
    CObj*      m_Owner;
    CAnimator* m_Animator;
    CSound*    m_pSound;


public:
    virtual void tick();


public:
    CLONE(CEffect_MonsterDead);
    CEffect_MonsterDead();
    CEffect_MonsterDead(CObj* _Owner);
    ~CEffect_MonsterDead();
};

