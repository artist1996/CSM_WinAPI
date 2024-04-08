#pragma once
#include "CObj.h"
class CDoor :
    public CObj
{
private:
    CTexture*  m_Img;
    CCollider* m_Collider;

    int        m_HP;

public:
    virtual void tick() override;
    virtual void render() override;

public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    CLONE(CDoor);
    CDoor();
    CDoor(Vec2 _Pos, Vec2 _Scale, int _HP);
    ~CDoor();
};

