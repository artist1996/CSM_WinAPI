#pragma once
#include "CAsset.h"


class CTexture :
    public CAsset
{
private:
    HDC         m_hDC;
    HBITMAP     m_hBit;
    BITMAP      m_Info;

private:
    virtual int Load(const wstring& _strFilePath) override;
    int Create(UINT _Width, UINT _Height);

public:
    HDC GetDC() { return m_hDC; }
    UINT GetWidth() { return m_Info.bmWidth; }
    UINT GetHeight() { return m_Info.bmHeight; }
    void SetWidth(LONG _Width) { m_Info.bmWidth = _Width; }
    void SetHeight(LONG _Height) { m_Info.bmHeight = _Height; }

public:
    CTexture();
    ~CTexture();

    friend class CAssetMgr;
};

