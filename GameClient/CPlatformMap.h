#pragma once
#include "CComponent.h"

struct tPlatformInfo
{
    Vec2 StartPos;
    Vec2 EndPos;
};

class CPlatform;

class CPlatformMap :
    public CComponent
{
private:
    vector<CPlatform*>    m_vecPlat;
    vector<tPlatformInfo> m_vecPlatInfo;
    tPlatformInfo         m_PlatInfo;
    UINT                  m_Idx;

public:
    virtual void finaltick();
    virtual void render();

public:
    //void Clicked(Vec2 _vMousePos);
    //void ReleasedClicked(Vec2 _vMousePos);
    

public:
    CLONE(CPlatformMap)
    CPlatformMap();
    ~CPlatformMap();
};

