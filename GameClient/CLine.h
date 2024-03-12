#pragma once
#include "CObj.h"
class CLine :
    public CObj
{
private:
    CCollider*      m_Collider;


public:
    //virtual void render() override;
    

public:
    CLONE(CLine)
    CLine();
    ~CLine();
};