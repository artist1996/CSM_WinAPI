#pragma once
#include "CUI.h"


class CUI_Warning :
    public CUI
{
private:
    CObj*      m_Target;
    CAnimator* m_Animator;

    CSound*    m_Sound;

    int        m_Count;

public:
    virtual void tick_ui() override;
    void SetTarget(CObj* _Target) { m_Target = _Target; }
    
    void Play();

public:
    CLONE(CUI_Warning);
    CUI_Warning();
    ~CUI_Warning();
};

