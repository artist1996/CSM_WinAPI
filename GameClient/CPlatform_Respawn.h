#pragma once
#include "CObj.h"
class CPlatform_Respawn :
    public CObj
{
private:
    CCollider* m_Collider;


public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:
    CLONE(CPlatform_Respawn);
    CPlatform_Respawn();
    CPlatform_Respawn(Vec2 _Pos, Vec2 _Scale);
    virtual ~CPlatform_Respawn();
};

