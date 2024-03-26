#pragma once
#include "CUI.h"

class CDummy;

class CFrameUI :
    public CUI
{
private:
    CDummy*          m_DummyObject;      // UI 내에서 렌더링 될 DummyObject

    CTexture*        m_Texture;          // 출력할 프레임 이미지의 아틀라스 이미지
    int              m_Frame;            // 프레임
    
    CUT_INFO         m_CutInfo;          // 자를 이미지 사이즈
    
public:
    void SetFrame(int _Frame)           { m_Frame = _Frame; }
    void SetTexture(CTexture* _Texture) { m_Texture = _Texture; }
    
    int GetMaxFrame();
    int GetCurFrame();
    const vector<tAnimFrm>& GetVecAnimationFrame();
    const tAnimFrm& GetCurFrameInfo();

    void ShowFrameImg(int _Frame);

    void AddMaxFrame();
    void AddCurFrame();
    void MinusCurFrame();

    bool IsEmpty();

    void SetFrameInfo(CUT_INFO _Info, float _Duration, Vec2 _Offset);
    Vec2 GetCurFrameOffset();
    
    void InitFrame(const wstring& _strKey, CTexture* _Tex);
    void Reset();
    
public:
    void EditStartPos(Vec2 _Pos);
    void EditEndPos(Vec2 _Pos);
    void EditOffset(Vec2 _Offset);
    void EditDuration(float _Duration);
    
public:
    virtual void begin() override;
    virtual void tick_ui() override;
    virtual void render_ui() override;

public:
    CLONE(CFrameUI);
    CFrameUI();
    ~CFrameUI();
};