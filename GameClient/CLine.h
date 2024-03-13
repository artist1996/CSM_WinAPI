#pragma once
#include "CObj.h"
class CLine :
    public CObj
{
private:
    CCollider*      m_Collider;


public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;
    
public:
    CLONE(CLine)
    CLine();
    CLine(Vec2 _StartPos, Vec2 _EndPos);
    ~CLine();
};