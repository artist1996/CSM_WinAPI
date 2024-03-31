#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CTaskMgr.h"

#include "CComponent.h"
#include "CAnimator.h"



CObj::CObj()
	: m_Type(LAYER_TYPE::NONE)
	, m_bDead(false)
	, m_Animator(nullptr)
	, m_eDir(DIRECTION::END)
	, m_Speed(0.f)
{
}

CObj::CObj(const CObj& _Other)
	: CEntity(_Other)
	, m_Pos(_Other.m_Pos)
	, m_PrevPos(_Other.m_PrevPos)
	, m_Scale(_Other.m_Scale)
	, m_Animator(nullptr)
	, m_Type(LAYER_TYPE::NONE)
	, m_bDead(false)
	, m_eDir(_Other.m_eDir)
{
	for (size_t i = 0; i < _Other.m_vecCom.size(); ++i)
	{
		AddComponent(_Other.m_vecCom[i]->Clone());
	}
}

CObj::~CObj()
{
	Safe_Del_Vec(m_vecCom);
}


void CObj::begin()
{
}

void CObj::tick()
{
	m_PrevPos = m_Pos;
}

void CObj::finaltick()
{
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		m_vecCom[i]->finaltick();
	}
}

void CObj::render()
{	
	if (nullptr == m_Animator)
		return;

	m_Animator->render();
}

void CObj::Destroy()
{
	tTask task = {};

	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param1 = (DWORD_PTR)this;

	CTaskMgr::GetInst()->AddTask(task);
}

CComponent* CObj::AddComponent(CComponent* _Component)
{
	m_vecCom.push_back(_Component);
	_Component->m_Owner = this;

	// ������Ʈ�� �߰��� ������Ʈ�� Animator �� ������ �����ͷ� ���� ����Ų��.
	if (nullptr == m_Animator)
	{
		m_Animator = dynamic_cast<CAnimator*>(_Component);
	}

	return _Component;
}