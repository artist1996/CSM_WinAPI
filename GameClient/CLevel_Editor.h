#pragma once
#include "CLevel.h"

class CPlatform;
class CTile;

struct tPlatformInfo
{
    Vec2 StartPos;
    Vec2 EndPos;
};

class CLevel_Editor :
    public CLevel
{
private:
    CPlatform* m_EditPlat;
    CTile*     m_EditTile;

    tPlatformInfo m_PlatInfo;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    CLevel_Editor();
    ~CLevel_Editor();
};

