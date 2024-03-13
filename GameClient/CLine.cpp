#include "pch.h"
#include "CLine.h"
#include "CCollider.h"

CLine::CLine()
	: m_Collider(nullptr)
{
}

CLine::CLine(Vec2 _StartPos, Vec2 _EndPos)
	: m_Collider(nullptr)
{
	SetPos(_StartPos);
	SetScale(_EndPos);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CLine::~CLine()
{
}

void CLine::begin()
{
}

void CLine::tick()
{
}

void CLine::render()
{
	if (L"Test" == GetName())
	{
		USE_PEN(DC, PEN_TYPE::PEN_GREEN);
		Vec2 vStartPos = CCamera::GetInst()->GetRenderPos(GetPos());
		Vec2 vEndPos = GetScale();
		MoveToEx(DC, vStartPos.x, vStartPos.y, nullptr);
		LineTo(DC, vEndPos.x, vEndPos.y);
	}
}