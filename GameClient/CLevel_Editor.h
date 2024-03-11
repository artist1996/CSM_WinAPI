#pragma once
#include "CLevel.h"

class CPlatform;
class CTile;
class CPlatformMap;

struct tInfo
{
    Vec2 StartPos;
    Vec2 EndPos;
};

class CLevel_Editor :
    public CLevel
{
private:
    CTile*             m_EditTile;
    vector<CPlatform*> m_vecEditPlat;
    CPlatform*         m_Platform;
    tInfo              m_Info;
    
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

