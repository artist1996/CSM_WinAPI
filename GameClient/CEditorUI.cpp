#include "pch.h"
#include "CEditorUI.h"
#include "CTexture.h"
#include "CEditor_Dummy.h"

CEditorUI::CEditorUI()
	: m_DummyObject(nullptr)
{
}

CEditorUI::CEditorUI(Vec2 _Pos, Vec2 _Scale)
{
	SetPos(_Pos);
	SetScale(_Scale);
}

CEditorUI::~CEditorUI()
{
}

void CEditorUI::SetImg(CTexture* _Img)
{
	m_DummyObject->SetImg(_Img);
}

void CEditorUI::begin()
{
	CUI::begin();
	m_DummyObject = new CEditor_Dummy;
	m_DummyObject->SetOwnerUI(this);
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	
	float x = ((vPos.x + vScale.x) - vScale.x) + 25.f;
	float y = ((vPos.y + vScale.y) - vScale.y) + 25.f;
	m_DummyObject->SetPos(Vec2(x,y));
	m_DummyObject->SetScale(Vec2(0.f, 0.f));
}

void CEditorUI::tick_ui()
{
}

void CEditorUI::render_ui()
{
	CUI::render_ui();
	
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	USE_PEN(DC, PEN_TYPE::PEN_BLACK);
	Rectangle(DC, (int)vPos.x, (int)vPos.y, (int)(vPos.x + vScale.x), (int)(vPos.y + vScale.y));

	if(nullptr != m_DummyObject)
		m_DummyObject->render();
}