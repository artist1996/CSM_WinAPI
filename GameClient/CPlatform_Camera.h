#pragma once
#include "CObj.h"
class CPlatform_Camera :
    public CObj
{
private:
    CCollider*      m_Collider;

    PLATFORM_CAMERA m_Type;

public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    CLONE(CPlatform_Camera);
    CPlatform_Camera();
    CPlatform_Camera(Vec2 _Pos, Vec2 _Scale, PLATFORM_CAMERA _Type);
    virtual ~CPlatform_Camera();
};

