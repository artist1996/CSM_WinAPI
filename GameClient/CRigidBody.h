#pragma once
#include "CComponent.h"
class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Velocity;          // (����, ũ��) �ӵ�
    Vec2    m_VelocityByGravity; // �߷¿� ���ؼ� �����ϴ� �ӵ�
    Vec2    m_AddVelocity;       // ���� �ӵ��� ������ �ӵ�
    Vec2    m_Force;             // ��

    float   m_Mass;              // ����

    float   m_MaxWalkSpeed;      // �ִ� �ӷ�
    float   m_MaxGravitySpeed;   // �ִ� �߷� �ӷ�
    float   m_InitWalkSpeed;     // �ּ� �ӷ�
                                 
    float   m_Friction;          // ������
    float   m_GravityAccel;      // �߷� ���ӵ�
                                 
    bool    m_UseGravity;        // �߷� üũ
    bool    m_Ground;            // �� ���� ���ִ��� üũ
                                 
    float   m_JumpSpeed;         // ���� �ӷ�
public:
    virtual void finaltick() override;
    void AddForce(Vec2 _Force)  { m_Force += _Force; }


    void SetMass(float _Mass)   { m_Mass = _Mass; }
    void SetMaxWalkSpeed(float _Speed)     { m_MaxWalkSpeed = _Speed; }
    void SetInitWalkSpeed(float _Speed)    { m_InitWalkSpeed = _Speed; }
    void SetFriction(float _Friction) { m_Friction = _Friction; }
    void SetMaxGravitySpeed(float _MaxGravitySpeed) { m_MaxGravitySpeed = _MaxGravitySpeed; }


    float GetMass() { return m_Mass; }
    float GetFriction() { return m_Friction; }
    float GetInitWalkSpeed() { return m_InitWalkSpeed; }
    float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
    float GetJumpSpeed() { return m_JumpSpeed; }
    Vec2  GetGravityVelocity() { return m_VelocityByGravity; }

    void UseGravity(bool _UseGravity)
    {
        m_UseGravity = _UseGravity;
        if (!m_UseGravity)
        {
            m_VelocityByGravity = Vec2(0.f, 0.f);
        }
    }

    void SetGround(bool _Ground)
    {
        m_Ground = _Ground;
        if (m_Ground)
        {
            m_VelocityByGravity = Vec2(0.f, 0.f);
        }
    }

    bool IsGround() { return m_Ground; }
  

public:
    CLONE(CRigidBody)

    CRigidBody();
    ~CRigidBody();
};

