#include "pch.h"
#include "CFrameUI.h"
#include "CDummy.h"

CFrameUI::CFrameUI()
	: m_DummyObject(nullptr)
	, m_Texture(nullptr)
	, m_Frame(0)
{
	SetName(L"FrameUI");
}

CFrameUI::~CFrameUI()
{
}

void CFrameUI::begin()
{
	CUI::begin();
	m_DummyObject = new CDummy;
	m_DummyObject->SetOwnerUI(this);
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	float x = (vPos.x + vScale.x) - vPos.x * 0.5f;
	float y = (vPos.y + vScale.y) - vPos.y * 0.5f;
	m_DummyObject->SetPos(Vec2(x, y));
	m_DummyObject->SetScale(Vec2(0.f, 0.f));
}

void CFrameUI::tick_ui()
{
}

void CFrameUI::render_ui()
{
	CUI::render_ui();
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	
	USE_PEN(DC, PEN_TYPE::PEN_BLACK);
	
	Rectangle(DC, (int)vPos.x, (int)vPos.y, (int)(vPos.x + vScale.x), (int)(vPos.y + vScale.y));
	
	//MoveToEx(DC, (int)(vPos.x), (int)(vPos.y + vScale.y * 0.5f), nullptr);
	//LineTo  (DC, (int)(vPos.x + vScale.x), (int)(vPos.y + vScale.y * 0.5f));
	//
	//MoveToEx(DC, (int)(vPos.x + vScale.x * 0.5f), (int)vPos.y, nullptr);
	//LineTo  (DC, (int)(vPos.x + vScale.x * 0.5f), (int)(vPos.y + vScale.y));

	if (nullptr == m_Texture)
		return;
}

int CFrameUI::GetMaxFrame()
{
	return m_DummyObject->GetMaxFrame();
}

int CFrameUI::GetCurFrame()
{
	return m_DummyObject->GetCurFrame();
}

const vector<tAnimFrm>& CFrameUI::GetVecAnimationFrame()
{
	return m_DummyObject->GetVecAnimationFrame();
}

const tAnimFrm& CFrameUI::GetCurFrameInfo()
{
	return m_DummyObject->GetCurFrameInfo();
}

void CFrameUI::ShowFrameImg(int _Frame)
{
	if (nullptr == m_Texture)
		return;
	
	m_DummyObject->ShowFrameImage(m_Texture, _Frame);
}

void CFrameUI::AddMaxFrame()
{
	m_DummyObject->AddMaxFrame();
}

void CFrameUI::AddCurFrame()
{
	m_DummyObject->AddCurFrame();
}

void CFrameUI::MinusCurFrame()
{
	m_DummyObject->MinusCurFrame();
}

bool CFrameUI::IsEmpty()
{
	return m_DummyObject->IsEmpty();
}

void CFrameUI::SetFrameInfo(CUT_INFO _Info, float _Duration, Vec2 _Offset)
{
	tAnimFrm frm = {};
	frm.StartPos = _Info.Start;
	frm.SliceSize = _Info.End;
	frm.Offset = _Offset;
	frm.Duration = _Duration;

	m_DummyObject->SetFrameInfo(frm);
}

Vec2 CFrameUI::GetCurFrameOffset()
{
	return m_DummyObject->GetCurFrameOffset();
}

void CFrameUI::InitFrame(const wstring& _strKey, CTexture* _Tex)
{
	m_DummyObject->InitFrame(_strKey, _Tex);
}

void CFrameUI::Reset()
{
	m_DummyObject->ResetFrame();
}

void CFrameUI::EditStartPos(Vec2 _Pos)
{
	m_DummyObject->EditStartPos(_Pos);
}

void CFrameUI::EditEndPos(Vec2 _Pos)
{
	m_DummyObject->EditEndPos(_Pos);
}

void CFrameUI::EditOffset(Vec2 _Offset)
{
	m_DummyObject->EditOffset(_Offset);
}

void CFrameUI::EditDuration(float _Duration)
{
	m_DummyObject->EditDuration(_Duration);
}
