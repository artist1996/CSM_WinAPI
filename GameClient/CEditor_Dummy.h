#pragma once
#include "CObj.h"

class CUI;

class CEditor_Dummy :
    public CObj
{
private:
    CUI*      m_UI;
    CTexture* m_Img;

public:
    void SetImg(CTexture* _Img) { m_Img = _Img; }
    void SetOwnerUI(CUI* _UI)   { m_UI = _UI; }
    virtual void render() override;

public:
    CLONE(CEditor_Dummy);
    CEditor_Dummy();
    ~CEditor_Dummy();
};