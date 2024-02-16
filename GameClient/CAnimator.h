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
    void LoadAnimation(const wstring& _strRelativeFilePath);


    CAnimation* FindAnimation(const wstring& _AnimName);

    void Play(const wstring& _AnimName, bool _Repeat);

public:
    CLONE(CAnimator);
    CAnimator();
    ~CAnimator();
};

