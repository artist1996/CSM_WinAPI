#pragma once
#include "CUI.h"
class CHUD_Player :
    public CUI
{
private:
    CTexture* m_HPBar;
    CTexture* m_Life;

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

public:
    CLONE(CHUD_Player);
    CHUD_Player();
    ~CHUD_Player();
};

