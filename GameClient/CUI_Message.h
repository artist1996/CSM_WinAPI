#pragma once
#include "CUI.h"
class CUI_Message :
    public CUI
{
private:
    CTexture* m_Img;

    Vec2      m_CenterPos;

    int       m_Type;

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

public:
    CLONE(CUI_Message);
    CUI_Message();
    CUI_Message(Vec2 _Pos, int _Type);
    virtual ~CUI_Message();
};

