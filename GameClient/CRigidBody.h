#pragma once
#include "CComponent.h"
class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Velocity;          // (방향, 크기) 속도
    Vec2    m_VelocityByGravity; // 중력에 의해서 증가하는 속도
    Vec2    m_AddVelocity;       // 최종 속도에 누적될 속도
    Vec2    m_Force;             // 힘

    float   m_Mass;              // 질량

    float   m_MaxWalkSpeed;      // 최대 속력
    float   m_MaxGravitySpeed;   // 최대 중력 속력
    float   m_InitWalkSpeed;     // 최소 속력
                                 
    float   m_Friction;          // 마찰력
    float   m_GravityAccel;      // 중력 가속도
                                 
    bool    m_UseGravity;        // 중력 체크
    bool    m_Ground;            // 땅 위에 서있는지 체크
                                 
    float   m_JumpSpeed;         // 점프 속력
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

