#pragma once
#include "CObj.h"
class CPlayer_JumpAttack :
    public CObj
{
private:
    CSound* m_pSound;
    CSound* m_HitSound;

    CObj* m_Owner;
    
    CCollider* m_Collider;
    CAnimator* m_Animator;

public:
    virtual void tick() override;
    void SetAnimator(CAnimator* _Animator) { m_Animator = _Animator; }
    void SetOwner(CObj* _Owner)            { m_Owner = _Owner; }
    
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

private:
    void JumpAttack();

public:
    CLONE(CPlayer_JumpAttack);
    CPlayer_JumpAttack();
    CPlayer_JumpAttack(CObj* _Owner, CAnimator* _Animator, Vec2 _Pos);
    ~CPlayer_JumpAttack();
};

