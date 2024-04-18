#pragma once
#include "CMonster.h"
class CMonster_Batton :
    public CMonster
{
private:
    CTexture*  m_BombImg;

    CCollider* m_Collider;
    CAnimator* m_Animator;
    CFSM*      m_FSM;

    bool       m_Bomb;
    
public:
    void SetBomb(bool _Bomb) { m_Bomb = _Bomb; }

public:
    virtual void begin() override;
    virtual void render() override;

public:
    CLONE(CMonster_Batton);
    CMonster_Batton();
    CMonster_Batton(Vec2 _Pos, Vec2 _Scale, int _HP, float _DetectRange);
    ~CMonster_Batton();
};