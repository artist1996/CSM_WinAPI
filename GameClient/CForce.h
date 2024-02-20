#pragma once
#include "CObj.h"
class CForce :
    public CObj
{
private:
    float   m_Force;        // 힘의 크기
    float   m_Range;        // 힘의 범위
    float   m_Time;         // 시간

    float   m_Age;          // 수명

public:
    void SetForce(float _Force, float _Range, float _Time)
    {
        m_Force = _Force;
        m_Range = _Range;
        m_Time = _Time;
    }

public:
    virtual void tick() override;

private:
    void AddForce(LAYER_TYPE _Type);

public:
    CLONE(CForce)
    CForce();
    ~CForce();
};