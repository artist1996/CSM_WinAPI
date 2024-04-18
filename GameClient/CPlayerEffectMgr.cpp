#include "pch.h"
#include "CPlayerEffectMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CObj.h"

#include "CEffect_Dash.h"
#include "CAfterImage.h"
#include "CEffect_Kick.h"

#include "CAnimator.h"
#include "CAnimation.h"

CPlayerEffectMgr::CPlayerEffectMgr()
	: m_DashCount(0)
	, m_KickCount(0)
{}

CPlayerEffectMgr::~CPlayerEffectMgr()
{
	//Safe_Del_Vec(m_vecDash);
	//Safe_Del_Vec(m_vecKick);
	//Safe_Del_Vec(m_vecShadow);
}

void CPlayerEffectMgr::Init()
{
	CObj* pObj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ZERO");

	CEffect_Dash* m_Dash = new CEffect_Dash(pObj, Vec2(0.f, 0.f), Vec2(20.f, 20.f));
	m_vecDash.push_back(m_Dash);
	m_Dash = new CEffect_Dash(pObj, Vec2(0.f, 0.f), Vec2(20.f, 20.f));
	m_vecDash.push_back(m_Dash);
	m_Dash = new CEffect_Dash(pObj, Vec2(0.f, 0.f), Vec2(20.f, 20.f));
	m_vecDash.push_back(m_Dash);
	m_Dash = new CEffect_Dash(pObj, Vec2(0.f, 0.f), Vec2(20.f, 20.f));
	m_vecDash.push_back(m_Dash);
	m_Dash = new CEffect_Dash(pObj, Vec2(0.f, 0.f), Vec2(20.f, 20.f));
	m_vecDash.push_back(m_Dash);
	m_Dash = new CEffect_Dash(pObj, Vec2(0.f, 0.f), Vec2(20.f, 20.f));
	m_vecDash.push_back(m_Dash);
	m_Dash = new CEffect_Dash(pObj, Vec2(0.f, 0.f), Vec2(20.f, 20.f));
	m_vecDash.push_back(m_Dash);
	for (size_t i = 0; i < m_vecDash.size(); ++i)
	{
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, m_vecDash[i]);
	}

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
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, m_vecShadow[i]);
	}

	CEffect_Kick* pKick = new CEffect_Kick;
	m_vecKick.push_back(pKick);
	pKick = new CEffect_Kick;
	m_vecKick.push_back(pKick);
	pKick = new CEffect_Kick;
	m_vecKick.push_back(pKick);

	for (size_t i = 0; i < m_vecKick.size(); ++i)
	{
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, m_vecKick[i]);
	}
}

void CPlayerEffectMgr::tick()
{
	if (m_DashCount == m_vecDash.size() - 1)
	{
		m_DashCount = 0;
	}

	if (m_KickCount == m_vecKick.size() - 1)
	{
		m_KickCount = 0;
	}
}

void CPlayerEffectMgr::Play(const wstring& _strName, bool _Play)
{
	for (size_t i = 0; i < m_vecShadow.size(); ++i)
	{
		m_vecShadow[i]->Play(_strName, _Play);
	}
}

void CPlayerEffectMgr::PlayDash(const wstring& _strName, bool _Play)
{
	m_vecDash[m_DashCount++]->Play(_strName, _Play);
}

void CPlayerEffectMgr::KickSetPos(Vec2 _Pos)
{
	m_vecKick[m_KickCount]->SetPos(_Pos);
}

void CPlayerEffectMgr::PlayKick(const wstring& _strName, bool _Play)
{
	m_vecKick[m_KickCount++]->Play(_strName, _Play);
}

void CPlayerEffectMgr::ChangeCurAnim(const wstring& _strName)
{
	for (size_t i = 0; i < m_vecShadow.size(); ++i)
	{
		m_vecShadow[i]->GetAnimator()->SetCurAnim(m_vecShadow[i]->GetAnimator()->FindAnimation(_strName));
	}
}

void CPlayerEffectMgr::DashSetPos(Vec2 _Pos)
{
	m_vecDash[m_DashCount]->SetPos(_Pos);
}

void CPlayerEffectMgr::SetActive(bool _Active)
{
	for (size_t i = 0; i < m_vecShadow.size(); ++i)
	{
		m_vecShadow[i]->SetActive(_Active);
	}
}

bool CPlayerEffectMgr::GetActive()
{
	for (size_t i = 0; i < m_vecShadow.size(); ++i)
	{
		bool bActive = m_vecShadow[i]->GetActive();

		if (bActive)
			return true;
	}

	return false;
}

void CPlayerEffectMgr::clear()
{
	m_vecDash.clear();
	m_vecShadow.clear();
	m_vecKick.clear();
}
