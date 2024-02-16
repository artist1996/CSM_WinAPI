#pragma once
#include "CEntity.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"

class CComponent;
class CCollider;
class CAnimator;
class CFSM;

class CObj :
    public CEntity
{
private:
    Vec2                m_Pos;      // ��ġ
    Vec2                m_Scale;    // ũ��
    vector<CComponent*> m_vecCom;   // ���� ������Ʈ��

    CAnimator*          m_Animator;

    LAYER_TYPE          m_Type;     // �Ҽ� ���̾�
    bool                m_bDead;    // ���� ��������

public:
    void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
    void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }

    Vec2 GetPos() { return m_Pos; }
    Vec2 GetScale() { return m_Scale; }
    LAYER_TYPE GetLayerType() { return m_Type; }
    bool IsDead() { return m_bDead; }

    void Destroy();

    CComponent* AddComponent(CComponent* _Component);

    template<typename T>
    T* GetComponent()
    {
        for (size_t i = 0; i < m_vecCom.size(); ++i)
        {
            T* pComponent = dynamic_cast<T*>(m_vecCom[i]);

            if(pComponent)
            {
                return pComponent;
            }
        }

        return nullptr;
    }

public:
    virtual void begin();
    virtual void tick();            // ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
    virtual void finaltick() final;// ������Ʈ�� ������ ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
    virtual void render();

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {}
    virtual void OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {}
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {}
    

public:
    virtual CObj* Clone() = 0; // { return new CObj(*this); }

public:
    CObj();
    ~CObj();

    friend class CLevel;
    friend class CTaskMgr;
};
