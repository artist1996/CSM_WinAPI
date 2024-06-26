#pragma once
#include "CUI.h"

class CHUD_Boss :
    public CUI
{
private:
    CTexture* m_Img;

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

public:
    CLONE(CHUD_Boss);
    CHUD_Boss();
    ~CHUD_Boss();
};

