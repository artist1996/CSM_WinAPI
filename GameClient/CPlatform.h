#pragma once
#include "CObj.h"

class CPlatformMap;

class CPlatform :
    public CObj
{
private:
    CPlatformMap* m_PlatMap;
    CCollider*    m_Collider;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void render() override;

public:
    void Clicked(Vec2 _vMousePos);
    void ReleasedClicked(Vec2 _vMousePos);

    CLONE(CPlatform)
public:
    CPlatform();
    CPlatform(Vec2 _StartPos, Vec2 _EndPos);
    CPlatform(Vec2 _Pos, Vec2 _Scale, LAYER_TYPE _type);
    ~CPlatform();
};

