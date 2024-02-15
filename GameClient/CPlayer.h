#pragma once
#include "CObj.h"


class CCollider;
class CAnimator;

class CPlayer :
    public CObj
{
private:
    float       m_Speed;

    CTexture*   m_PlayerImg;


    CCollider*  m_HeadCol;
    CCollider*  m_BodyCol;
    CAnimator*  m_Animator;

public:
    virtual void begin();
    virtual void tick();        // ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����   
  
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;

public:
    virtual CObj* Clone() override { return new CPlayer(*this); };

public:
    CPlayer();
    ~CPlayer();
};

