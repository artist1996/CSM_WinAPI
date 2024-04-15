#pragma once
#include "CObj.h"
class CEffect_Dash :
    public CObj
{
private:
    CObj* m_Owner;

    CAnimator* m_Animator;

    float      m_Dir;

    bool       m_Active;
    bool       m_Play;

public:
    virtual void tick() override;
    virtual void render() override;

    void Play(const wstring& _strName, bool _Play);

public:
    CLONE(CEffect_Dash);
    CEffect_Dash(CObj* _Owner, Vec2 _Pos, Vec2 _Scale);
    ~CEffect_Dash();
};

