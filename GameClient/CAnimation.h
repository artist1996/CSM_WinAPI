#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_Animator;     // Animation �� �����ϰ� �ִ� Animator
    CTexture*           m_Atlas;        // Animation �̹����� �����ϰ� �ִ� Altas Texture
    vector<tAnimFrm>    m_vecFrm;       // �� ������ ����

    HBRUSH              m_OldBrush;

    float               m_Time;         // �����ð� üũ

    int                 m_CurFrmIdx;    // ���� ������
    bool                m_bFinish;      // �ִϸ��̼� ����� ������� �˸�

    bool                m_Hit;

public:
    void finaltick();
    void render();
    void Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);
    void Create(CTexture* _AtlasTex, vector<tAnimFrm> _vecFrm);
    bool IsFinish() { return m_bFinish; }

    void Save(const wstring& _strRelativeFolderPath);

    int  Load(const wstring& _strRelativeFilePath);

    int LoadAnimation(const wstring& _strFullPath);

    tAnimFrm& GetFrame(int _Frame)        { return m_vecFrm[_Frame]; }     // Frame ���� ��ȯ �Լ�
    const vector<tAnimFrm>& GetVecFrame() { return m_vecFrm; };
    
    CTexture* GetImg() { return m_Atlas; }

    void SetCurFrameIdx(int _Idx) { m_CurFrmIdx = _Idx; }
    int GetCurFrameIdx()          { return m_CurFrmIdx; }

    void Reset()
    {
        m_Time = 0.f;
        m_CurFrmIdx = 0;
        m_bFinish = false;
    }

    void Reset(int _Idx)
    {
        m_Time = 0.f;
        m_CurFrmIdx = _Idx;
        m_bFinish = false;
    }

public:
    CLONE(CAnimation);

public:
    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};

