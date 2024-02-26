#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"


CTexture::CTexture()
    : m_hDC{}
    , m_hBit{}
    , m_Info{}
{
}

CTexture::~CTexture()
{
    DeleteDC(m_hDC);
    DeleteObject(m_hBit);
}

int CTexture::Load(const wstring& _strFilePath)
{
    m_hBit = (HBITMAP) LoadImage(nullptr, _strFilePath.c_str()
                                , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if (nullptr == m_hBit)
    {
        MessageBox(nullptr, L"��Ʈ�� �ε� ����", L"Asset �ε� ����", MB_OK);
        return E_FAIL;
    }

    // �ε�� ��Ʈ���� ������ Ȯ���Ѵ�.
    GetObject(m_hBit, sizeof(BITMAP), &m_Info);

    // DC �� �������Ѽ� �ε�� ��Ʈ���̶� �����Ѵ�.
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    DeleteObject(SelectObject(m_hDC, m_hBit));

    return S_OK;
}

int CTexture::Create(UINT _Width, UINT _Height)
{
    // DC ����
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
 
    // Bitmap ����
    m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _Width, _Height);
    
    HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBitmap);

    // �ε�� ��Ʈ���� ������ Ȯ���Ѵ�.
    GetObject(m_hBit, sizeof(BITMAP), &m_Info);
    return S_OK;
}
