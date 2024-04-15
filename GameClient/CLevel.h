#pragma once
#include "CEntity.h"

class CObj;
class CCollider;
class CPlatform;
class CLine;
class CSound;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>       m_arrObj[(UINT)LAYER_TYPE::END];
    vector<CCollider*>  m_arrCollider[(UINT)LAYER_TYPE::END];

    SAVE_TYPE           m_Save;

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

    void SavePlatform(const wstring& _strRelativePath);
    void SaveLine(const wstring& _strRelativePath);
    void SaveMonster(const wstring& _strRelativePath);
    void SaveTrap(const wstring& _strRelativePath);

    void LoadPlatform(const wstring& _strRelativePath);
    void LoadLine(const wstring& _strRelativePath);
    void LoadMonster(const wstring& _strRelativePath);
    void LoadTrap(const wstring& _strRelativePath);

    void SetSaveType(SAVE_TYPE _Type) { m_Save = _Type; }

public:
    CLONE_DISABLE(CLevel)
    CLevel();
    ~CLevel();

    friend class CUIMgr;
};

