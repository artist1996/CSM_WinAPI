#pragma once
#include "CUI.h"
class CHUD_PlayerHP :
    public CUI
{
private:
    CObj*     m_Owner;
    CTexture* m_Img;

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

public:
    CLONE(CHUD_PlayerHP);
    CHUD_PlayerHP();
    ~CHUD_PlayerHP();
};

