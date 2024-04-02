#pragma once
#include "CObj.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CPlayer :
    public CObj
{
private:
    CTexture*       m_PlayerImg;

    CCollider*      m_BodyCol;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;
    CFSM*           m_FSM;

    float           m_InvincibleTime;
    bool            m_Invincible;

    float           m_Speed;
    
    PLAYER_STATE    m_eState;

public:
    virtual void begin();
    virtual void tick();        // 오브젝트가 매 프레임마다 해야할 작업을 구현   
    virtual void render();
  
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

    float GetSpeed()                    { return m_Speed; }

    void SetState(PLAYER_STATE _eState) { m_eState = _eState; }
    PLAYER_STATE GetState()             { return m_eState; }

public:
    void CreateAttack(ATTACK_TYPE _Type);
    void CreateJumpAttack();

private:
    void Jump();
    void Shoot();

public:
    virtual CObj* Clone() override { return new CPlayer(*this); };

public:
    CPlayer();
    CPlayer(const CPlayer& _Other);
    ~CPlayer();

    friend class CState_Player;
    friend class CState_PlayerAnim;
};

