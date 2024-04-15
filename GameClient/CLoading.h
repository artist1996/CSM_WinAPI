#pragma once
#include "CBackGround.h"
class CLoading :
    public CBackGround
{
private:
    CAnimator* m_Animator;

public:
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CLoading);
    CLoading();
    ~CLoading();
};

