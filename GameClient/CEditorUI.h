#pragma once
#include "CUI.h"

class CEditor_Dummy;

class CEditorUI :
    public CUI
{
private:
    CEditor_Dummy* m_DummyObject;
    
    

public:
    void SetImg(CTexture* _Img);
    virtual void begin() override;
    virtual void tick_ui() override;
    virtual void render_ui() override;
    
public:
    CLONE(CEditorUI);
    CEditorUI();
    CEditorUI(Vec2 _Pos, Vec2 _Scale);
    ~CEditorUI();
};

