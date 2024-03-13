#pragma once
#include "CEntity.h"

class CObj;
class CCollider;
class CPlatform;
class CLine;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>       m_arrObj[(UINT)LAYER_TYPE::END];
    vector<CCollider*>  m_arrCollider[(UINT)LAYER_TYPE::END];

protected:
    vector<CPlatform*> m_vecEditPlat;
    CPlatform*         m_Platform;
    tInfo              m_Info;

    vector<CLine*>     m_vecEditLine;
    CLine*             m_Line;
    
public:
    // 시점 함수
    virtual void begin(); // 레벨이 시작될 때
    virtual void tick();    // 매 프레임마다 호출
    virtual void finaltick(); // 매 프레임마다 호출
    virtual void render();  // 매프레임마다 호출

    virtual void Enter() PURE;
    virtual void Exit() PURE;

public:
    void AddObject(LAYER_TYPE _Layer, CObj* _Obj);
    void RegisterCollider(CCollider* _Collider);
    CObj* FindObjectByName(const wstring& _Name);
    CObj* FindObjectByName(LAYER_TYPE _Type, const wstring& _Name);

    const vector<CObj*>& GetObjects(LAYER_TYPE _Type) { return m_arrObj[(UINT)_Type]; }
    const vector<CCollider*>& GetColliders(LAYER_TYPE _Layer) {  return m_arrCollider[(UINT)_Layer];  }

protected:
    void DeleteAllObjects();
    void DeleteObjects(LAYER_TYPE _Type);
    void LoadFromPlatform(const wstring& _strRelativePath);
    void LoadFromLine(const wstring& _strRelativePath);

public:
    CLONE_DISABLE(CLevel)
    CLevel();
    ~CLevel();
};

