#pragma once

#include "CComponent.h"



class CCollider :
    public CComponent
{
private:
    Vec2    m_OffsetPos;    // ���� ������Ʈ�κ��� ������� ��ǥ
    Vec2    m_Scale;

    Vec2    m_FinalPos;     // ���� ��ǥ ( ���� ������Ʈ ������ + ������ ���� )

    UINT    m_CollisionCount;

    bool    m_Active;       // �浹ü Ȱ��ȭ, ��Ȱ��ȭ ����
    bool    m_bRegister;    // �浹ü�� ������ ������� ������ ����
    

public:
    void SetOffsetPos(Vec2 _Offset) { m_OffsetPos = _Offset; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    Vec2 GetFinalPos() { return m_FinalPos; }
    Vec2 GetScale() { return m_Scale; }

    void SetActive(bool _Set) 
    { 
        m_Active = _Set;

        if (m_Active)
        {
            m_bRegister = true;
        }
    }

    bool IsActive() { return m_Active; }


private:
    void BeginOverlap(CCollider* _OtherCollider);
    void OnOverlap(CCollider* _OtherCollider);
    void EndOverlap(CCollider* _OtherCollider);

public:
    virtual void finaltick() override;
    virtual CCollider* Clone() { return new CCollider(*this); }

public:
    CCollider();
    CCollider(const CCollider& _Other);
    ~CCollider();

    friend class CCollisionMgr;
};

 