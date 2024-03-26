#pragma once
#include "CBackGround.h"

class CTexture;
class CAnimator;

class CLogo :
    public CBackGround
{
private:
    CAnimator*    m_Animator;
   
public:
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CLogo);
    CLogo();
    ~CLogo();
};

