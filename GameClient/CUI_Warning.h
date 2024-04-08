#pragma once
#include "CUI.h"
class CUI_Warning :
    public CUI
{
private:
    CAnimator* m_Animator;

    int        m_Count;

public:
    virtual void tick_ui() override;

public:
    CLONE(CUI_Warning);
    CUI_Warning();
    ~CUI_Warning();
};

