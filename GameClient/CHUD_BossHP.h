#pragma once
#include "CUI.h"
class CHUD_BossHP :
    public CUI
{
private:
    CObj*     m_Owner;
    CTexture* m_Img;

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

public:
    CLONE(CHUD_BossHP);
    CHUD_BossHP();
    ~CHUD_BossHP();
};

