#pragma once
#include "CLevel.h"


class CLevel_Stage01 :
    public CLevel
{
private:


public:

public:
    virtual void tick() override;
    virtual CLevel_Stage01* Clone() override { return new CLevel_Stage01(*this); }

public:
    CLevel_Stage01();
    ~CLevel_Stage01();
};

