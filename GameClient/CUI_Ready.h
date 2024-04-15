#pragma once
#include "CUI.h"
class CUI_Ready :
    public CUI
{
private:
    CAnimator* m_Animator;
    CSound*    m_Sound;
    float      m_Time;
    bool       m_bPlay;

public:
    virtual void tick_ui() override;


public:
    CLONE(CUI_Ready);
    CUI_Ready();
    CUI_Ready(Vec2 _Pos);
    ~CUI_Ready();
};

