#pragma once
#include "CObj.h"
class CEditor_RenderDummy :
    public CObj
{
private:
    CTexture* m_Img;
    OBJ_ID    m_ID;
    int       m_HP;
    float     m_DetectRange;

public:
    virtual void render() override;
    OBJ_ID GetID()  { return m_ID; }
    int GetHP()      { return m_HP; }
    float GetRange() { return m_DetectRange; }

public:
    CLONE(CEditor_RenderDummy);
    CEditor_RenderDummy();
    CEditor_RenderDummy(Vec2 _Pos, Vec2 _Scale, OBJ_ID _ID, int _HP, float _DetectRange);
    virtual ~CEditor_RenderDummy();
};

