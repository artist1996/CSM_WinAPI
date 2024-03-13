#pragma once
#include "CBackGround.h"
class CStage01 :
    public CBackGround
{
private:
    
public:
    virtual void render() override;
    

public:
    CLONE(CStage01)
    CStage01();
    ~CStage01();
};

