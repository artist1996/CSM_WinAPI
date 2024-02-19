#pragma once
#include "CComponent.h"
class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Velocity; // (방향, 크기) 속도
    Vec2    m_Force;    // 힘

    float   m_Mass;     // 질량

    float   m_MaxWalkSpeed;     // 최대 속력

public:
    virtual void finaltick() override;
    void AddForce(Vec2 _Force)  { m_Force += _Force; }
    void SetMass(float _Mass)   { m_Mass = _Mass; }

    float GetMass()                    { return m_Mass; }
    void SetMaxWalkSpeed(float _Speed) { m_MaxWalkSpeed = _Speed; }


public:
    CLONE(CRigidBody)

    CRigidBody();
    ~CRigidBody();
};

