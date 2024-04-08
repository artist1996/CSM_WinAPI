#pragma once
#include "CObj.h"

class CMonster :
    public CObj
{
private:
    int         m_HP;

    float       m_DetectRange;
    float       m_Speed;

    float       m_Time;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

    void SetHP(int _HP)               { m_HP = _HP; }
    void SetDetectRange(float _Range) { m_DetectRange = _Range; }
    void SetSpeed(float _Speed)       { m_Speed = _Speed; }
    
    int GetHP()                       { return m_HP; }
    float GetSpeed()                  { return m_Speed; }
    float GetDetectRange()            { return m_DetectRange; }

public:
    CLONE(CMonster);
    CMonster();
    CMonster(Vec2 _Pos, Vec2 _Scale);
    ~CMonster();
};

