#pragma once
#include "CComponent.h"
class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Velocity; // (����, ũ��) �ӵ�
    Vec2    m_Force;    // ��

    float   m_Mass;     // ����

    float   m_MaxWalkSpeed;     // �ִ� �ӷ�
    float   m_InitWalkSpeed;    // �ּ� �ӷ�

    float   m_Friction;         // ������

public:
    virtual void finaltick() override;
    void AddForce(Vec2 _Force)  { m_Force += _Force; }
    void SetMass(float _Mass)   { m_Mass = _Mass; }

    float GetMass()                         { return m_Mass; }
    void  SetMaxWalkSpeed(float _Speed)     { m_MaxWalkSpeed = _Speed; }
    void  SetInitWalkSpeed(float _Speed)    { m_InitWalkSpeed = _Speed; }
    void  SetFriction(float _Friction)      { m_Friction = _Friction; }
    
    float GetFriction() { return m_Friction; }
    float GetInitWalkSpeed() { return m_InitWalkSpeed; }
    float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }

public:
    CLONE(CRigidBody)

    CRigidBody();
    ~CRigidBody();
};

