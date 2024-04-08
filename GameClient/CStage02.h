#pragma once
#include "CBackGround.h"
class CStage02 :
    public CBackGround
{
private:

public:
    virtual void render() override;

public:
    CLONE(CStage02);
    CStage02();
    ~CStage02();
};