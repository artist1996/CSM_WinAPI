#pragma once
#include "CBackGround.h"
class CSelect :
    public CBackGround
{
private:

public:
    virtual void render() override;

public:
    CLONE(CSelect);
    CSelect();
    ~CSelect();
};

