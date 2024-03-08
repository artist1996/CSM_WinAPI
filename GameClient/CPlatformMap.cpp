#include "pch.h"
#include "CPlatformMap.h"
#include "CPlatform.h"
#include "CLevelMgr.h"

CPlatformMap::CPlatformMap()
	: m_Idx(0)
{
}

CPlatformMap::~CPlatformMap()
{
	Safe_Del_Vec(m_vecPlat);
}

void CPlatformMap::finaltick()
{
}

void CPlatformMap::render()
{
	if (m_vecPlat.empty())
	{
		return;
	}

	for (size_t i = 0; i < m_vecPlat.size(); ++i)
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		Rectangle(DC, (int)m_vecPlat[i]->GetPos().x, (int)m_vecPlat[i]->GetPos().y
					, (int)m_vecPlat[i]->GetScale().x, (int)m_vecPlat[i]->GetScale().y);
		SpawnObject(pLevel, LAYER_TYPE::PLATFORM, m_vecPlat[i]);
	}
}

//void CPlatformMap::Clicked(Vec2 _vMousePos)
//{
//	_vMousePos = CCamera::GetInst()->GetRealPos(_vMousePos);
//	
//	m_PlatInfo.StartPos = _vMousePos;
//}
//
//void CPlatformMap::ReleasedClicked(Vec2 _vMousePos)
//{
//	_vMousePos = CCamera::GetInst()->GetRealPos(_vMousePos);
//	m_PlatInfo.EndPos = _vMousePos;
//	m_vecPlatInfo.push_back(m_PlatInfo);
//	
//	CPlatform* pPlat = new CPlatform;
//	pPlat->SetPos(m_PlatInfo.StartPos);
//	pPlat->SetScale(m_PlatInfo.EndPos);
//
//	m_vecPlat.push_back(pPlat);
//	m_vecPlatInfo.clear();
//}
