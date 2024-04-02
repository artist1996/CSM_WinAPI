#include "pch.h"
#include "CSoundMgr.h"
#include "CEngine.h"
#include "CSound.h"

CSoundMgr::CSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{}

CSoundMgr::~CSoundMgr()
{
	m_pSound->Release();
}

int CSoundMgr::init()
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"���� �Ŵ��� �ʱ�ȭ ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (nullptr != m_pBGM)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}