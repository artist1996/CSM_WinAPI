#pragma once
#include "CMonster.h"
class CMonster_GigaDeath :
    public CMonster
{
private:
    
public:
    virtual void tick() override;

public:
    CLONE(CMonster_GigaDeath);
    CMonster_GigaDeath();
    ~CMonster_GigaDeath();
};