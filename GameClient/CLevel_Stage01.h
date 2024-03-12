#pragma once
#include "CLevel.h"

class CPlatform;

class CLevel_Stage01 :
    public CLevel
{
private:
    vector<CPlatform*> m_vecEditPlat;
    CPlatform*         m_Platform;

public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    CLevel_Stage01();
    ~CLevel_Stage01();
};

