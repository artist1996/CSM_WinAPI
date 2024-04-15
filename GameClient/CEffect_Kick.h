#pragma once
#include "CObj.h"
class CEffect_Kick :
    public CObj
{
private:
    CObj*      m_Owner;
    CAnimator* m_Animator;
    bool       m_Play;

public:
    void Play(const wstring& _strName, bool _Play);

public:
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CEffect_Kick);
    CEffect_Kick();
    virtual ~CEffect_Kick();
};

