#pragma once
#include "CComponent.h"

typedef void(*CALL_BACK)(void);
typedef void(CObj::*DELEGATE)(void);

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

    bool    m_Wall;              // 벽에 부딪혔는지 체크
    bool    m_PrevWall;          // 이전 프레임 벽이었는지 체크

    bool    m_Block;             // 막다른 길 체크

    bool    m_Jump;              // 점프 중인지 체크

    float   m_JumpSpeed;         // 점프 속력

    CALL_BACK m_GroundFunc;
    CALL_BACK m_AirFunc;

    CObj*    m_GroundInst;
    DELEGATE m_GroundDelegate;

    CObj*    m_AirInst;
    DELEGATE m_AirDelegate;

public:
    virtual void finaltick() override;
    void AddForce(Vec2 _Force)  { m_Force += _Force; }


    void SetMass(float _Mass)                       { m_Mass = _Mass; }
    void SetMaxWalkSpeed(float _Speed)              { m_MaxWalkSpeed = _Speed; }
    void SetInitWalkSpeed(float _Speed)             { m_InitWalkSpeed = _Speed; }
    void SetFriction(float _Friction)               { m_Friction = _Friction; }
    void SetMaxGravitySpeed(float _MaxGravitySpeed) { m_MaxGravitySpeed = _MaxGravitySpeed; }
    void SetJumpSpeed(float _JumpSpeed)             { m_JumpSpeed = _JumpSpeed; }

    float GetMass()            { return m_Mass; }
    float GetFriction()        { return m_Friction; }
    float GetInitWalkSpeed()   { return m_InitWalkSpeed; }
    float GetMaxWalkSpeed()    { return m_MaxWalkSpeed; }
    float GetJumpSpeed()       { return m_JumpSpeed; }
    Vec2  GetGravityVelocity() { return m_VelocityByGravity; }
    
    void SetGroundFunc(void (*_pFunc)(void)) { m_GroundFunc = _pFunc; }
    void SetAirFunc(void(*_pFunc)(void))     { m_AirFunc = _pFunc; }

    void SetGroundDelegate(CObj* _Inst, DELEGATE _MemFunc)
    {
        m_GroundInst = _Inst;
        m_GroundDelegate = _MemFunc;
    }
    
    void SetAirDelegate(CObj* _Inst, DELEGATE _MemFunc)
    {
        m_AirInst = _Inst;
        m_AirDelegate = _MemFunc;
    }
    
    void SetVelocityByGravity(Vec2 _Gravity) { m_VelocityByGravity = _Gravity; }

    void SetGround(bool _Ground)
    {
        if (m_Ground == _Ground)
            return;

        m_Ground = _Ground;

        if (m_Ground)
        {
            m_VelocityByGravity = Vec2(0.f, 0.f);
            
            if (nullptr != m_GroundFunc)
                m_GroundFunc();

            if (m_GroundInst && m_GroundDelegate)
                (m_GroundInst->*m_GroundDelegate)();
        }

        else
        {
            if (nullptr != m_AirFunc)
                m_AirFunc();

            if (m_AirInst && m_AirDelegate)
                (m_AirInst->*m_AirDelegate)();
        }
    }

    void SetWall(bool _Wall)
    {
        if (m_Wall == _Wall)
            return;

        m_Wall = _Wall;
    }

    void SetBlock(bool _Block)
    {
        if (m_Block == _Block)
            return;

        m_Block = _Block;
    }

    void SetJump(bool _Jump) { m_Jump = _Jump; }


    void UseGravity(bool _UseGravity)
    {
        m_UseGravity = _UseGravity;
        if (!m_UseGravity)
        {
            m_VelocityByGravity = Vec2(0.f, 0.f);   
        }
    }

    bool IsWall()       { return m_Wall; }
    bool IsGround()     { return m_Ground; }
    bool IsPrevWall()   { return m_PrevWall; }
    bool IsBlock()      { return m_Block; }
   
    void Jump();
    bool IsJump()     { return m_Jump; }

public:
    CLONE(CRigidBody)

    CRigidBody();
    CRigidBody(const CRigidBody& _Other);
    ~CRigidBody();
};

