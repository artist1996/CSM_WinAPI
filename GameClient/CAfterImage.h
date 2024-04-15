#pragma once
#include "CObj.h"

class CAfterImage :
    public CObj
{
private:
    CObj*      m_Owner;

    CAnimator* m_Animator;

    bool       m_bActive;
    bool       m_bRender;

    float      m_Time;
    float      m_RenderTime;

public:
    void Play(const wstring& _strName, bool _Play);
    void SetActive(bool _Active)  { m_bActive = _Active; }
    bool GetActive()              { return m_bActive; }

    CAnimator* GetAnimator() { return m_Animator; }

public:
    virtual void tick() override;
    virtual void render() override;

public:
    CLONE(CAfterImage);
    CAfterImage(CObj* _Owner, Vec2 _Pos);
    virtual ~CAfterImage();
};