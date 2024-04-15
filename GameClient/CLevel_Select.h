#pragma once
#include "CLevel.h"

class CUI_Select;
class CDummy_Select;

class CLevel_Select :
    public CLevel
{
private:
    CUI_Select*    m_UI;

    CDummy_Select* m_Zero;
    CDummy_Select* m_X;

    CSound*        m_Sound;
    CSound*        m_Sound2;
    CSound*        m_Sound3;

    float m_Time;

    bool  m_bZero;
    bool  m_bX;
    
    bool  m_bChange;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLevel_Select();
    ~CLevel_Select();
};

