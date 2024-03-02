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
    
    template <typename T>
    T GetBlackboardData(const wstring& _strDataName) { return m_Owner->GetBlackboardData<T>(_strDataName); }

public:
    virtual void Enter() PURE;
    virtual void FinalTick() PURE;
    virtual void Exit() PURE;
    
public:
    CState();
    ~CState();

    friend class CFSM;
};

