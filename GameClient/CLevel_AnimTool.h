#pragma once
#include "CLevel.h"

class CTexture;
class CAnimator;
class CPlayer;
class CUI;

class CLevel_AnimTool :
    public CLevel
{
private:
    HMENU             m_hMenu;
    HWND              m_Dialog;
    CUI*              m_AtlasUI;
    CUI*              m_FrameUI;
    CUI*              m_AnimationUI;
    
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void render() override;

    CUI* GetAtlasUI()     { return m_AtlasUI; }
    CUI* GetFrameUI()     { return m_FrameUI; }
    CUI* GetAnimationUI() { return m_AnimationUI; }
    
    void SetDialog(HWND _Dialog) { m_Dialog = _Dialog; }
    HWND GetDialog()             { return m_Dialog; }

public:
    void SaveAnimation();
    void LoadAnimation();

public:
    CLevel_AnimTool();
    ~CLevel_AnimTool();
};

