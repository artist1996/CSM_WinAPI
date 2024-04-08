#include "pch.h"
#include "CShadowMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CObj.h"

#include "CAfterImage.h"

CShadowMgr::CShadowMgr()
{}

CShadowMgr::~CShadowMgr()
{}

void CShadowMgr::Init()
{
	CObj* pObj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ZERO");

	CAfterImage* pShadow = new CAfterImage(pObj, Vec2(pObj->GetPos().x - 100.f, pObj->GetPos().y));
	m_vecShadow.push_back(pShadow);
	CAfterImage* pShadow2 = new CAfterImage(pShadow, Vec2(pShadow->GetPos().x - 100.f, pObj->GetPos().y));
	m_vecShadow.push_back(pShadow2);
	CAfterImage* pShadow3 = new CAfterImage(pShadow2, Vec2(pShadow2->GetPos().x - 100.f, pObj->GetPos().y));
	m_vecShadow.push_back(pShadow3);
	CAfterImage* pShadow4 = new CAfterImage(pShadow3, Vec2(pShadow3->GetPos().x - 100.f, pObj->GetPos().y));
	m_vecShadow.push_back(pShadow4);
	CAfterImage* pShadow5 = new CAfterImage(pShadow4, Vec2(pShadow4->GetPos().x - 100.f, pObj->GetPos().y));
	m_vecShadow.push_back(pShadow5);

	for (size_t i = 0; i < m_vecShadow.size(); ++i)
	{
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::SHADOW, m_vecShadow[i]);
	}

}

void CShadowMgr::Play(const wstring& _strName, bool _Play)
{
	for (size_t i = 0; i < m_vecShadow.size(); ++i)
	{
		m_vecShadow[i]->Play(_strName, _Play);
	}
}

void CShadowMgr::SetActive(bool _Active)
{
	for (size_t i = 0; i < m_vecShadow.size(); ++i)
	{
		m_vecShadow[i]->SetActive(_Active);
	}
}

bool CShadowMgr::GetActive()
{
	for (size_t i = 0; i < m_vecShadow.size(); ++i)
	{
		bool bActive = m_vecShadow[i]->GetActive();

		if (bActive)
			return true;
	}

	return false;
}
