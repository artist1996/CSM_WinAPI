#include "pch.h"
#include "CPanel.h"

CPanel::CPanel()
{
}

CPanel::~CPanel()
{
}

void CPanel::tick_ui()
{
	if (IsLbtnDowned())
	{
		Vec2 vCurMousePos = CKeyMgr::GetInst()->GetMousePos();
		
		Vec2 vDiff = vCurMousePos - m_vDownPos;

		Vec2 vNextPos = GetFinalPos() + vDiff;

		SetPos(vNextPos);

		m_vDownPos = vCurMousePos;
	}
}

void CPanel::LButtonDown()
{
	CUI::LButtonDown();

	m_vDownPos = CKeyMgr::GetInst()->GetMousePos();

	wchar_t szBuff[50] = {};
	swprintf_s(szBuff, L"x : %f, y : %f", m_vDownPos.x, m_vDownPos.y);
	LOG(LOG_TYPE::DBG_WARNING, szBuff);
}
