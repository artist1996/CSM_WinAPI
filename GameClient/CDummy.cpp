#include "pch.h"
#include "CDummy.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPathMgr.h"
#include "CLevelMgr.h"
#include "CUI.h"
#include "CLevel.h"
#include "CLevel_AnimTool.h"
#include "CFrameUI.h"
#include "CAnimationUI.h"
#include "CAtlasUI.h"

CDummy::CDummy()
	: m_UI(nullptr)
	, m_Img(nullptr)
	, m_Animator(nullptr)
	, m_MaxFrame(0)
	, m_CurFrame(0)
	, m_Repeat(false)
	, m_FrmInfo{}
	, m_bArray{}
{
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	//m_Animator->LoadAnimation(L"animation\\player\\WALK_DOWN.anim");
	//m_Animator->LoadAnimation(L"animation\\player\\START.anim");
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, this);
}

CDummy::~CDummy()
{
}

void CDummy::ShowFrameImage(CTexture* _pTex, int _Frame)
{
	if (m_vecFrm.empty())
		return;

	m_Img = _pTex;

	if (nullptr == m_Img)
		return;

	
	tAnimFrm frm = m_vecFrm[_Frame];
}

void CDummy::SetFrameInfo(tAnimFrm _frm)
{
	m_FrmInfo = _frm;

	if (m_vecFrm.empty())
	{
		m_vecFrm.push_back(m_FrmInfo);
		m_bArray[m_CurFrame] = true;
		return;
	}

	if (true == m_bArray[m_CurFrame])
	{
		m_vecFrm[m_CurFrame].StartPos = m_FrmInfo.StartPos;
		m_vecFrm[m_CurFrame].SliceSize = m_FrmInfo.SliceSize;
		m_vecFrm[m_CurFrame].Offset = m_FrmInfo.Offset;
		m_vecFrm[m_CurFrame].Duration = m_FrmInfo.Duration;
		return;
	}
	
	m_vecFrm.push_back(m_FrmInfo);
	m_bArray[m_CurFrame] = true;
}

void CDummy::ResetFrame()
{
	if (L"FrameUI" == m_UI->GetName())
	{
		m_vecFrm.clear();
		m_vecFrm.resize(0);
		m_Img = nullptr;
		m_CurFrame = 0;
		m_MaxFrame = 0;
		memset(&m_bArray, false, sizeof(bool) * 50);
		m_strKey = {};
		m_Repeat = false;
	}
}

void CDummy::ResetAnimation()
{
}

void CDummy::InitFrame(const wstring& _strKey, CTexture* _Img)
{
	m_Img = _Img;
	
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
	
	CUI* pUI = pTool->GetAnimationUI();
	CAnimationUI* pAnimUI = dynamic_cast<CAnimationUI*>(pUI);
	CAnimator* pAnimatior = pAnimUI->GetAnimator();

	wstring strFileName = _strKey;

	CAnimation* pAnim = pAnimatior->FindByAnimationName(pAnimatior->GetCurAnim()->GetName());
	
	const vector<tAnimFrm>& vecFrm = pAnim->GetVecFrame();

	m_strKey = pAnim->GetName();
	m_Repeat = false;
	m_MaxFrame = (int)vecFrm.size();
	m_CurFrame = 0;

	for (size_t i = 0; i < vecFrm.size(); ++i)
	{
		tAnimFrm frm = {};

		frm.StartPos = vecFrm[i].StartPos;
		frm.SliceSize = vecFrm[i].SliceSize;
		frm.Offset = vecFrm[i].Offset;
		frm.Duration = vecFrm[i].Duration;

		m_vecFrm.push_back(frm);
		m_bArray[i] = true;
	}
}

void CDummy::InitAnimation(const wstring& _strKey)
{
	CAnimation* pAnim = m_Animator->FindByAnimationName(_strKey);
	if (nullptr == pAnim)
		return;
	
	m_Animator->SetCurAnim(pAnim);
}

void CDummy::SaveAnimation(const wstring& _strRelativePath)
{
	m_vecFrm.clear();
	m_vecFrm.resize(0);
	m_strKey = {};
	m_Img = nullptr;
	m_MaxFrame = 0;
	m_CurFrame = 0;
	m_Animator->SetCurAnim(nullptr);
}

void CDummy::LoadAnimation(const wstring& _strKey)
{
	m_Animator->LoadToolAnimation(_strKey);
	m_Img = m_Animator->GetCurAnim()->GetImg();
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);

	CUI* pUI = pTool->GetFrameUI();
	CUI* pUI2 = pTool->GetAtlasUI();
	CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI);
	CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI2);
	
	pFrameUI->Reset();
	pFrameUI->InitFrame(_strKey, m_Img);
	pAtlasUI->Reset();
	tAnimFrm frm = pFrameUI->GetCurFrameInfo();
	CUT_INFO info = {};

	info.Start = frm.StartPos;
	info.End = frm.StartPos + frm.SliceSize;
	pAtlasUI->Init(m_Img, info);	
}

void CDummy::tick()
{
	CObj::tick();
}

void CDummy::render()
{
	CObj::render();

	if (L"ANIMATIONUI" == m_UI->GetName())
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		USE_PEN(DC, PEN_TYPE::PEN_RED);
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_BLACK);
		Ellipse(DC, (int)(vPos.x - 10.f * 0.5f), (int)(vPos.y - 10.f * 0.5f), (int)(vPos.x + 10.f * 0.5f), (int)(vPos.y + 10.f * 0.5f));
	}

	else
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		USE_PEN(DC, PEN_TYPE::PEN_RED);
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_BLACK);
		Ellipse(DC, (int)(vPos.x - 10.f * 0.5f), (int)(vPos.y - 10.f * 0.5f), (int)(vPos.x + 10.f * 0.5f), (int)(vPos.y + 10.f * 0.5f));
	}

	if (m_vecFrm.empty())
		return;

	if (nullptr == m_Img)
		return;

	if (m_CurFrame >= m_vecFrm.size())
		return;

	tAnimFrm frm = {};
	frm.StartPos = m_vecFrm[m_CurFrame].StartPos;
	frm.SliceSize = m_vecFrm[m_CurFrame].SliceSize;
	frm.Offset = m_vecFrm[m_CurFrame].Offset;
	frm.Duration = m_vecFrm[m_CurFrame].Duration;
	
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;
	Vec2 vPos = GetPos();
	
	AlphaBlend(DC, (int)(vPos.x - frm.SliceSize.x * 0.5f + frm.Offset.x)
				 , (int)(vPos.y - frm.SliceSize.y * 0.5f + frm.Offset.y)
				 , (int)frm.SliceSize.x, (int)frm.SliceSize.y
				 , m_Img->GetDC()
				 , (int)frm.StartPos.x, (int)frm.StartPos.y
				 , (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
}

void CDummy::PlayAnimation(const wstring& _strName, bool _Repeat)
{
	if (nullptr == m_Animator)
		return;

	m_strKey = _strName;
	m_Repeat = _Repeat;

	m_Animator->Play(m_strKey, m_Repeat);
}

void CDummy::CreateAnimation(const wstring& _strName, const vector<tAnimFrm>& _vecFrm, CTexture* _Img)
{
	if (nullptr == m_Animator)
		return;

	m_Animator->CreateAnimation(_strName, _Img, _vecFrm);

	m_vecFrm.clear();
	m_vecFrm.resize(0);
	m_strKey = {};
	m_Img = nullptr;
	m_MaxFrame = 0;
	m_CurFrame = 0;
	m_Animator->SetCurAnim(nullptr);
	
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
	CUI* pUI = pTool->GetFrameUI();
	CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI);
	pFrameUI->Reset();
}

void CDummy::EditStartPos(Vec2 _Pos)
{
	if (L"FrameUI" != m_UI->GetName())
		return;
	
	m_vecFrm[m_CurFrame].StartPos += _Pos;
}

void CDummy::EditEndPos(Vec2 _Pos)
{
	if (L"FrameUI" != m_UI->GetName())
		return;

	m_vecFrm[m_CurFrame].SliceSize += _Pos;
}

void CDummy::EditOffset(Vec2 _Offset)
{
	if (L"FrameUI" != m_UI->GetName())
		return;

	m_vecFrm[m_CurFrame].Offset += _Offset;
}

void CDummy::EditDuration(float _Duration)
{
	if (L"FrameUI" != m_UI->GetName())
		return;

	m_vecFrm[m_CurFrame].Duration += _Duration;
}