#pragma once
#include "CObj.h"
class CDummy_Magma :
    public CObj
{
private:
    CTexture* m_Img;

public:
    virtual void render() override;

public:
    CLONE(CDummy_Magma);
    CDummy_Magma();
    virtual ~CDummy_Magma();
};

