#pragma once
#include "CLevel.h"
class CLevel_Loading :
    public CLevel
{
private:
    float   m_Time;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLevel_Loading();
    ~CLevel_Loading();
};

