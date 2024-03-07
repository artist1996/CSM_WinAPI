#pragma once
#include "CLevel.h"


class CLevel_Stage01 :
    public CLevel
{
private:


public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual CLevel_Stage01* Clone() override { return new CLevel_Stage01(*this); }

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLevel_Stage01();
    ~CLevel_Stage01();
};

