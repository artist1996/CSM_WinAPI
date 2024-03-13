#pragma once
#include "CLevel.h"

class CPlatform;
class CTexture;
class CLine;
class CTile;
class CBackGround;

class CLevel_Editor :
    public CLevel
{
private:
    CTile*             m_EditTile;
    
    CPlatform*         m_TestPlatform;
    tInfo              m_TestInfo;

    CLine*             m_TestLine;

    MAP_TYPE           m_Type;

    CTexture*          m_CurImg;
    
    CBackGround*       m_BackGround;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    void SaveToPlatformFile(const wstring& _strRelativePath);
    void SaveToLineFile(const wstring& _strRelativePath);
    void ResetInfo()
    {
        memset(&m_Info, sizeof(tInfo), 0);
        memset(&m_TestInfo, sizeof(tInfo), 0);
    }
    void SetType(MAP_TYPE _Type) { m_Type = _Type; }

    void CreateUI();

public:
    CLevel_Editor();
    ~CLevel_Editor();
};

