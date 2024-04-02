#pragma once
#include "CState.h"
class CState_GigaDeath :
    public CState
{
private:
   
public:
    virtual void Enter() PURE;
    virtual void FinalTick() PURE;
    virtual void Exit() PURE;

public:
    CState_GigaDeath();
    virtual ~CState_GigaDeath();
};

