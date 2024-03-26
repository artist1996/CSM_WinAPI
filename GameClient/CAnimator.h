#pragma once
#include "CComponent.h"


class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;
    CAnimation*                 m_CurAnim;

    bool                        m_Repeat;

public:
    virtual void finaltick() override;
    void render();

    void CreateAnimation(const wstring& _AnimName, CTexture* _Atlas
                        , Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);
    void CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, vector<tAnimFrm> _vecFrame);
    void LoadAnimation(const wstring& _strRelativeFilePath);
    void LoadToolAnimation(const wstring& _strFullPath);


    CAnimation* FindAnimation(const wstring& _AnimName);
    CAnimation* FindByAnimationName(const wstring& _AnimName);



    void Play(const wstring& _AnimName, bool _Repeat);

    map<wstring, CAnimation*>& GetAnimationmap() { return m_mapAnim; }

    CAnimation* GetCurAnim()                     { return m_CurAnim; }
    void SetCurAnim(CAnimation* _CurAnim)        { m_CurAnim = _CurAnim; }

public:
    CLONE(CAnimator);
    CAnimator();
    CAnimator(const CAnimator& _Other);
    ~CAnimator();
};