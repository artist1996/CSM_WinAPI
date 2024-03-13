#pragma once
#include "CObj.h"

class CUI :
    public CObj
{
private:
    CUI*         m_ParentUI;
    vector<CUI*> m_vecChildUI;

    Vec2         m_vFinalPos;

    bool         m_MouseOn;
    bool         m_MouseOnPrev;
    bool         m_MouseLbtnDown;

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

    bool IsMouseOn()     { return m_MouseOn; }
    bool IsMouseOnPrev() { return m_MouseOnPrev; }
    bool IsLbtnDowned() { return m_MouseLbtnDown; }

    void AddChildUI(CUI* _UI)
    {
        m_vecChildUI.push_back(_UI);
        m_ParentUI = this;
    }

public:
    virtual void tick() final;
    virtual void render() final;
    
    virtual void tick_ui() PURE;
    virtual void render_ui();

public:
    virtual void LButtonDown();
    virtual void LButtonUp();
    virtual void LButtonClicked();

private:
    virtual void CheckMouseOn();

public:
    CUI();
    virtual ~CUI();

    friend class CTaskMgr;
};