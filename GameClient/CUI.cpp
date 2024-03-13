#include "pch.h"
#include "CUI.h"
#include "CTaskMgr.h"

CUI::CUI()
	: m_ParentUI(nullptr)
	, m_MouseOn(false)
	, m_MouseOnPrev(false)
	, m_MouseLbtnDown(false)
{
}

CUI::~CUI()
{
}

void CUI::tick()
{
	m_vFinalPos = GetPos();
	
	if (m_ParentUI)
	{
		m_vFinalPos += m_ParentUI->GetFinalPos();
	}

	CheckMouseOn();

	if (KEY_RELEASED(KEY::LBTN) && m_MouseLbtnDown)
	{
		CTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::UI_LBTN_DOWN, (DWORD_PTR)this, false });
	}

	tick_ui();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick();
	}

}

void CUI::render()
{
	CObj::render();
	render_ui();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render();
	}

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(DC, (int)vPos.x, (int)vPos.y, (int)(vPos.x + vScale.x), (int)(vPos.y + vScale.y));
}

void CUI::render_ui()
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	Rectangle(DC, (int)vPos.x, (int)vPos.y, (int)(vPos.x + vScale.x), (int)(vPos.y + vScale.y));
}

void CUI::LButtonDown()
{
	m_MouseLbtnDown = true;
}

void CUI::LButtonUp()
{
}

void CUI::LButtonClicked()
{	
}

void CUI::CheckMouseOn()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	
	m_MouseOnPrev = m_MouseOn;

	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x
		&& vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
	{
		m_MouseOn = true;
	}

	else
	{
		m_MouseOn = false;
	}
}