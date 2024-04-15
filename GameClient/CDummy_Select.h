#pragma once
#include "CObj.h"
class CDummy_Select :
    public CObj
{
private:
    CAnimator* m_Animator;

    int m_Type;
    bool m_Move;

public:
    virtual void tick() override;
    void Play(const wstring& _strName, bool _Repeat);

public:
    CLONE(CDummy_Select);
    CDummy_Select();
    CDummy_Select(Vec2 _Pos, int _Type);
    virtual ~CDummy_Select();
};

