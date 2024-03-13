#pragma once
#include "CObj.h"
class CBackGround :
    public CObj
{
private:
    CTexture*   m_Img;
    
public:
    virtual void tick();
    virtual void render() override;

public:
    void SetImg(CTexture* _Img) { m_Img = _Img; }
    CTexture* GetImg()          { return m_Img; }
    UINT GetWidth() { return m_Img->GetWidth(); }
    UINT GetHeight() { return m_Img->GetHeight(); }

public:
    CLONE(CBackGround)
    CBackGround();
    ~CBackGround();
};

