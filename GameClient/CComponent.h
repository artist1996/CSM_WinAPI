#pragma once
#include "CEntity.h"

#include "CObj.h"

class CComponent :
    public CEntity
{
private:
    CObj*       m_Owner;    // ������Ʈ�� �����ϰ� �ִ� ������Ʈ

public:
    CObj* GetOwner() { return m_Owner; }

public:
    virtual void finaltick() = 0;
    virtual CComponent* Clone() = 0;

public:
    CComponent();
    CComponent(const CComponent& _Other);
    virtual ~CComponent();

    friend class CObj;
};

