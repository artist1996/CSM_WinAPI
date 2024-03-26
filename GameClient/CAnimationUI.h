#pragma once
#include "CUI.h"

class CAnimator;
class CDummy;

class CAnimationUI :
    public CUI
{
private:
    CDummy*    m_DummyObject;
    
    wstring    m_strKey;
    bool       m_Repeat;

public:
    virtual void render_ui() override;
    void SetPlay(const wstring& _strKey, bool _Repeat)
    { 
        m_strKey = _strKey;
        m_Repeat = _Repeat;
    }

    void PlayAnimation(const wstring& _strName, bool _Repeat);
    CAnimator* GetAnimator();

    void CreateAnimation(const wstring& _strName, const vector<tAnimFrm>& _vecFrm, CTexture* _Img);

    void SaveAnimation(const wstring& _RelativeFilePath);
    void LoadAnimation(const wstring& _strKey);

    virtual void begin() override;
    virtual void tick_ui() override;
    
    void InitAnimation(const wstring& _strKey);

    void Reset();
    
public:
    CLONE(CAnimationUI);
    CAnimationUI();
    ~CAnimationUI();
};