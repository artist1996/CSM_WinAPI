#pragma once
#include "CUI.h"

class CTexture;

class CAtlasUI :
    public CUI
{
private:
    vector<CTexture*> m_vecTex;         // 모든 Texture 관리하는 벡터
    CTexture*         m_Texture;        // 지정한 Texture render

    CUT_INFO          m_CutInfo;        // 해당 아틀라스 애니메이션 프레임 잘라줄 정보 구조체

    bool              m_bMouse;

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

public:
    void SetAtlasTexture(const wstring& _strName);

    CTexture* GetAtlasTexture()        { return m_Texture; }
    vector<CTexture*> GetVecTexture()  { return m_vecTex; }
    void SetCutInfo(CUT_INFO _Info)    { m_CutInfo = _Info; }
    CUT_INFO GetCutInfo()              { return m_CutInfo; }
    void SetMouseClicekd(bool _Mouse)  { m_bMouse = _Mouse; }
    
public:
    void EditStartPos(Vec2 _Pos) { m_CutInfo.Start += _Pos; }
    void EditEndPos(Vec2 _Pos)   { m_CutInfo.End += _Pos; }

public:
    void Reset()
    {
        m_Texture = nullptr;
        memset(&m_CutInfo, 0, sizeof(CUT_INFO));
        m_bMouse = false;
    }

    void ResetCutInfo()
    {
        memset(&m_CutInfo, 0, sizeof(CUT_INFO));
    }

    void Init(CTexture* _Tex, CUT_INFO _Info)
    {
        m_Texture = _Tex;
        m_CutInfo = _Info;
    }

public:
    CLONE(CAtlasUI);
    CAtlasUI();
    ~CAtlasUI();
};