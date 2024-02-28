#pragma once
#include "CEntity.h"
#include "CFSM.h"

class CState :
    public CEntity
{
private:
    CFSM*       m_Owner;

protected:
    CObj* GetObj() { return m_Owner->GetOwner(); }
    CFSM* GetFSM() { return m_Owner; }
    
    void* GetBlackboardData(const wstring& _strDataName) {}

public:
    virtual void Enter() PURE;
    virtual void FinalTick() PURE;
    virtual void Exit() PURE;
    
public:
    CState();
    ~CState();

    friend class CFSM;
};

