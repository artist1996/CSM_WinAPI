#pragma once
#include "CObj.h"

class CUI;
class CAnimation;

class CDummy :
    public CObj
{
private:
    CUI*        m_UI;               // UI의 센터에 렌더링
    CTexture*   m_Img;              // 애니메이션 출력용 텍스쳐
    CAnimator*  m_Animator;         // 애니메이션 Play 시킬 Animator

    vector<tAnimFrm> m_vecFrm;      // 미리보기 기능 담당 할 벡터
    tAnimFrm         m_FrmInfo;
    int              m_CurFrame;
    int              m_MaxFrame;    // MaxFrame
    bool             m_bArray[50];

    wstring          m_strKey;
    bool             m_Repeat;


public:
    CAnimator* GetAnimator() { return m_Animator; }

    bool IsEmpty()           { return m_vecFrm.empty(); }
    
    void SetOwnerUI(CUI* _UI) { m_UI = _UI; }
    void PlayAnimation(const wstring& _strName, bool _Repeat);
    void ShowFrameImage(CTexture* _pTex, int _Frame);
    void CreateAnimation(const wstring& _strName,const vector<tAnimFrm>& _vecFrm, CTexture* _Img);
    
    void SetFrameInfo(tAnimFrm _frm);

    Vec2 GetCurFrameOffset()                       { return m_vecFrm[m_CurFrame].Offset; }
    const tAnimFrm& GetCurFrameInfo()
    { 
        if (IsEmpty())
            return m_FrmInfo;

        if (m_CurFrame >= m_vecFrm.size())
            return m_FrmInfo;

        return m_vecFrm[m_CurFrame];
    }
    tAnimFrm GetAnimationFrame(int _Frame)         { return m_vecFrm[_Frame]; }
    const vector<tAnimFrm>& GetVecAnimationFrame() { return m_vecFrm; }
    
    void EditStartPos(Vec2 _Pos);
    void EditEndPos(Vec2 _Pos);
    void EditOffset(Vec2 _Offset);
    void EditDuration(float _Duration);

    int GetMaxFrame()    { return m_MaxFrame; }
    int GetCurFrame()    { return m_CurFrame; }

    void AddMaxFrame()   { m_MaxFrame += 1; }
    void AddCurFrame()
    {
        m_CurFrame += 1;
        if (m_MaxFrame <= m_CurFrame)
        {
            m_CurFrame = m_MaxFrame - 1;
        }
    }
    void MinusCurFrame() 
    {
        if (0 == m_CurFrame)
            return;

        m_CurFrame -= 1;
    }

    void ResetFrame();
    void ResetAnimation();
    void InitFrame(const wstring& _strKey, CTexture* _Img);
    void InitAnimation(const wstring& _strKey);
    
    void SaveAnimation(const wstring& _strRelativePath);
    void LoadAnimation(const wstring& _strKey);

    virtual void tick() override;
    virtual void render() override;
public:
    CLONE(CDummy);
    CDummy();
    ~CDummy();
};