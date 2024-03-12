#pragma once
#include "CLevel.h"

class CPlatform;
class CTile;

class CLevel_Editor :
    public CLevel
{
private:
    CTile*             m_EditTile;
    
    CPlatform*         m_TestPlatform;
    tInfo              m_TestInfo;
    
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    void SaveToFile(const wstring& _strRelativePath);
    virtual void LoadFromFile(const wstring& _strRelativePath);

public:
    CLevel_Editor();
    ~CLevel_Editor();
};

