#pragma once
#include "CLevel.h"

class CTexture;
class CLogo;

class CLevel_Logo :
    public CLevel
{
private:
    CSound*   m_pSound;
    CLogo*    m_Logo;
    CTexture* m_Img;
    
    int       m_Count;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLONE_DISABLE(CLevel_Logo);
    CLevel_Logo();
    ~CLevel_Logo();
};

