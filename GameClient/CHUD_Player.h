#pragma once
#include "CUI.h"
class CHUD_Player :
    public CUI
{
private:
    CObj*     m_Owner;
    CTexture* m_HPBar;

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

    void SetImg(const wstring& _strName) { m_HPBar = CAssetMgr::GetInst()->FindTexture(_strName); }

public:
    CLONE(CHUD_Player);
    CHUD_Player();
    ~CHUD_Player();
};

