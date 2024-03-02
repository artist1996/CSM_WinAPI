#pragma once
#include "CObj.h"

class CMonster :
    public CObj
{
private:
    int         m_HP;
    
    float       m_DetectRange;
    float       m_Speed;


    CCollider*  m_Collider;
    CFSM*       m_FSM;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;





    virtual CMonster* Clone() { return new CMonster(*this); }
public:
    CMonster();
    ~CMonster();
};

