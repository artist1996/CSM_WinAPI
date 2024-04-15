#pragma once
#include "CUI.h"
class CUI_Select :
    public CUI
{
private:
    CAnimator* m_Animator;

    bool       m_Zero;
    bool       m_X;

public:
    void SetZero(bool _Zero)
    {
        SetPos(Vec2(590.f, 490.f));
        m_Zero = _Zero;
        m_X = false;
    };
    void SetX(bool _X)
    {
        SetPos(Vec2(210.f, 490.f));
        m_X = _X;
        m_Zero = false;
    };

    

    void Play(const wstring& _strName);

    virtual void tick_ui() override;
   
public:
    CLONE(CUI_Select);
    CUI_Select();
    ~CUI_Select();
};

