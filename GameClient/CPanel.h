#pragma once
#include "CUI.h"
class CPanel :
    public CUI
{
private:
    Vec2    m_vDownPos;

public:
    virtual void tick_ui() override;
    virtual void LButtonDown() override;

public:
    CLONE(CPanel);
    CPanel();
    ~CPanel();
};

