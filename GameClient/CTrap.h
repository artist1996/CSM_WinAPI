#pragma once
#include "CObj.h"
class CTrap :
    public CObj
{
private:    
    Vec2  m_StartPos;

protected:
    void SetStartPos(Vec2 _Pos) { m_StartPos = _Pos; }

public:
    Vec2 GetStartPos()          { return m_StartPos; }

public:
    virtual void tick() PURE;
    
public:
    CTrap();
    virtual ~CTrap();
};

