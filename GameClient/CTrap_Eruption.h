#pragma once
#include "CTrap.h"
class CTrap_Eruption :
    public CTrap
{
private:
    CCollider*  m_Collider;
    CAnimator*  m_Animator;
    
    float       m_Time;
    float       m_Range;

    bool        m_bActive;

public:
    virtual void tick() override;
    float GetRange() { return m_Range; }

public:
    CLONE(CTrap_Eruption);
    CTrap_Eruption();
    CTrap_Eruption(Vec2 _Pos, OBJ_ID _ID);
    ~CTrap_Eruption();
};

