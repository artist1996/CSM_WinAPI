#include "pch.h"
#include "CLevelMgr.h"

#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLevel_Stage01.h"
#include "CLevel_Editor.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);

	//for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	//{
	//	if (nullptr != m_arrLevel[i])
	//	{
	//		delete m_arrLevel[i];
	//	}
	//}
}


void CLevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CLevel_Editor;

	// 현재 레벨 지정
	//m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];
	
	::ChangeLevel(LEVEL_TYPE::EDITOR);
	
	//m_pCurrentLevel->begin();
}

void CLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	// 레벨안에 있는 물체들이 매프레임마다 할일을 정의함
	m_pCurrentLevel->tick();		// 오브젝트가 할일을 구현
	m_pCurrentLevel->finaltick();	// 컴포넌트가 할일을 구현
}

void CLevelMgr::render()
{
	if (nullptr == m_pCurrentLevel)
		return;

	m_pCurrentLevel->render();
}

CObj* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	return m_pCurrentLevel->FindObjectByName(_strName);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _NextLevelType)
{
	if (m_pCurrentLevel == m_arrLevel[(UINT)_NextLevelType])
	{
		return;
	}

	if (m_pCurrentLevel)
	{
		m_pCurrentLevel->Exit();
	}
	
	m_pCurrentLevel = m_arrLevel[(UINT)_NextLevelType];

	assert(m_pCurrentLevel);

	m_pCurrentLevel->Enter();
	
	m_pCurrentLevel->begin();
}