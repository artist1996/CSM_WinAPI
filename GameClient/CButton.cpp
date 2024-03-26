#include "pch.h"
#include "CButton.h"

CButton::CButton()
	: m_Func(nullptr)
	, m_NormalImg(nullptr)
	, m_HoverImg(nullptr)
	, m_DownImg(nullptr)
{
}

CButton::~CButton()
{
}

void CButton::tick_ui()
{
}

void CButton::render_ui()
{
	if (IsLbtnDowned())
	{
		if (nullptr == m_DownImg)
			CUI::render_ui();
	}

	else if (IsMouseOn())
	{
		if (nullptr == m_HoverImg)
			CUI::render_ui();
	}

	else
	{
		if (nullptr == m_NormalImg)
			CUI::render_ui();
	}
}

void CButton::LButtonClicked()
{
	if (nullptr != m_Func)
	{
		m_Func();
	}
}