#pragma once
#include "CLevel.h"
class CLevel_Stage02 :
    public CLevel
{
private:
    CSound* m_pBGM;
    
    float   m_Time;
    bool    m_Ready;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLevel_Stage02();
    virtual ~CLevel_Stage02();
};