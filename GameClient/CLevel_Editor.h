#pragma once
#include "CLevel.h"

class CPlatform;
class CTexture;
class CLine;
class CTile;
class CBackGround;

class CUI;

class CLevel_Editor :
    public CLevel
{
private:
    CTile*             m_EditTile;
    CUI*               m_UI;
    
    tInfo              m_tInfo;
    MAP_TYPE           m_Type;

    OBJ_ID             m_ID;

    CTexture*          m_CurImg;
    CBackGround*       m_BackGround;
    
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    void Platform();
    void Line();
    void Monster();
    void Trap();
    
    void ResetInfo()
    {
        memset(&m_tInfo, sizeof(tInfo), 0);
    }
    void SetType(MAP_TYPE _Type) { m_Type = _Type; }

    void CreateUI();

public:
    virtual void render() override;

public:
    CLevel_Editor();
    ~CLevel_Editor();
};

