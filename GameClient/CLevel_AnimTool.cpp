#include "pch.h"
#include "resource.h"
#include "CLevel_AnimTool.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CAtlasUI.h"
#include "CAnimationUI.h"
#include "CFrameUI.h"
#include "CDummy.h"

CLevel_AnimTool::CLevel_AnimTool()
	: m_AtlasUI(nullptr)
    , m_AnimationUI(nullptr)
    , m_FrameUI(nullptr)
    , m_hMenu(nullptr)
    , m_Dialog(nullptr)
{
    m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_GAMECLIENT));
}

CLevel_AnimTool::~CLevel_AnimTool()
{
    DestroyMenu(m_hMenu);
}

void CLevel_AnimTool::begin()
{
    CLevel::begin();
}

void CLevel_AnimTool::tick()
{
    CLevel::tick();

    //if (KEY_TAP(KEY::_0))
    //{
    //    ChangeLevel(LEVEL_TYPE::LOGO_START);
    //}
}

void CLevel_AnimTool::Enter()
{

    SetMenu(CEngine::GetInst()->GetMainWnd(), m_hMenu);
    CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution(), true);

    m_AtlasUI = new CAtlasUI;
    m_AtlasUI->SetPos(Vec2(0.f, 0.f));
    m_AtlasUI->SetScale(Vec2(CEngine::GetInst()->GetResolution().x, CEngine::GetInst()->GetResolution().y));

    m_FrameUI = new CFrameUI;
    m_FrameUI->SetPos(Vec2(400.f, 300.f));
    m_FrameUI->SetScale(Vec2(400.f, 300.f));

    m_AnimationUI = new CAnimationUI;
    m_AnimationUI->SetPos(Vec2(400.f, 0.f));
    m_AnimationUI->SetScale(Vec2(400.f, 300.f));

    AddObject(LAYER_TYPE::UI, m_AtlasUI);
    AddObject(LAYER_TYPE::UI, m_FrameUI);
    AddObject(LAYER_TYPE::UI, m_AnimationUI);
}

void CLevel_AnimTool::Exit()
{
    SetMenu(CEngine::GetInst()->GetMainWnd(), nullptr);
    CEngine::GetInst()->ChangeWindowSize(Vec2(800.f,600.f), false);
}

void CLevel_AnimTool::render()
{
    CLevel::render();
}

void CLevel_AnimTool::SaveAnimation()
{
    wchar_t szSelect[256] = {};

    OPENFILENAME ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szSelect;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szSelect);
    ofn.lpstrFilter = L"ANIM\0*.anim\0ALL\0*.*";
    ofn.nFilterIndex = 0;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;

    wstring strInitPath = CPathMgr::GetInst()->GetContehtPath();
    strInitPath += L"animation\\";
    ofn.lpstrInitialDir = strInitPath.c_str();

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetSaveFileName(&ofn))
    {
        CAnimationUI* pAnimationUI = dynamic_cast<CAnimationUI*>(m_AnimationUI);
     
        if (nullptr == pAnimationUI)
            return;

        CAnimator* pAnimator = pAnimationUI->GetAnimator();
        
        CAnimation* pAnimation = pAnimator->GetCurAnim();

        if (nullptr == pAnimation)
        {
            return;
        }

        pAnimation->Save(szSelect);
    }
}

void CLevel_AnimTool::LoadAnimation()
{
    wchar_t szSelect[256] = {};

    OPENFILENAME ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szSelect;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szSelect);
    ofn.lpstrFilter = L"ANIM\0*.anim";
    ofn.nFilterIndex = 0;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;

    wstring strInitPath = CPathMgr::GetInst()->GetContehtPath();
    strInitPath += L"animation\\";
    ofn.lpstrInitialDir = strInitPath.c_str();

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileName(&ofn))
    {
        CAnimationUI* pAnimationUI = dynamic_cast<CAnimationUI*>(m_AnimationUI);
        pAnimationUI->LoadAnimation(szSelect);
        
        CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(m_FrameUI);
        CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(m_AtlasUI);

        wchar_t szBuff[256] = {};
        swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().StartPos.x);
        SetDlgItemText(m_Dialog, IDC_STARTPOSX, szBuff);
        swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().StartPos.y);
        SetDlgItemText(m_Dialog, IDC_STARTPOSY, szBuff);
        swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().SliceSize.x);
        SetDlgItemText(m_Dialog, IDC_SLICESIZEX, szBuff);
        swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().SliceSize.y);
        SetDlgItemText(m_Dialog, IDC_SLICESIZEY, szBuff);
        swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().Offset.x);
        SetDlgItemText(m_Dialog, IDC_OFFSETX, szBuff);
        swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().Offset.y);
        SetDlgItemText(m_Dialog, IDC_OFFSETY, szBuff);
        swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().Duration);
        SetDlgItemText(m_Dialog, IDC_DURATION, szBuff);
        SetDlgItemInt(m_Dialog, IDC_MAXFRAME, pFrameUI->GetMaxFrame(), true);
        SetDlgItemInt(m_Dialog, IDC_FRAME, pFrameUI->GetCurFrame(), true);
        swprintf_s(szBuff, L"%s", pAnimationUI->GetAnimator()->GetCurAnim()->GetImg()->GetKey().c_str());
        SetDlgItemText(m_Dialog, IDC_TEXTURENAMEINPUT, szBuff);
        swprintf_s(szBuff, L"%s", pAnimationUI->GetAnimator()->GetCurAnim()->GetName().c_str());
        SetDlgItemText(m_Dialog, IDC_ANIMATIONNAMEINPUT, szBuff);
    }
}

INT_PTR CALLBACK TextureSelectProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK AnimationSelectProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK AnimInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {

    case WM_INITDIALOG:
    {
        CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
        CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
        pTool->SetDialog(hDlg);
    }
        return (INT_PTR)TRUE;
        break;   
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDC_STARTPOSX_MINUS:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pAtlasUI->EditStartPos(Vec2(-1.f, 0.f));
            pFrameUI->EditStartPos(Vec2(-1.f, 0.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pAtlasUI->GetCutInfo().Start.x);
            SetDlgItemText(hDlg, IDC_STARTPOSX, szBuff);
        }
            break;
        case IDC_STARTPOSX_ADD:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pAtlasUI->EditStartPos(Vec2(1.f, 0.f));
            pFrameUI->EditStartPos(Vec2(1.f, 0.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pAtlasUI->GetCutInfo().Start.x);
            SetDlgItemText(hDlg, IDC_STARTPOSX, szBuff);
        }
            break;
        case IDC_STARTPOSY_MINUS:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pAtlasUI->EditStartPos(Vec2(0.f, -1.f));
            pFrameUI->EditStartPos(Vec2(0.f, -1.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pAtlasUI->GetCutInfo().Start.y);
            SetDlgItemText(hDlg, IDC_STARTPOSY, szBuff);
        }
            break;
        case IDC_STARTPOSY_ADD:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pAtlasUI->EditStartPos(Vec2(0.f, 1.f));
            pFrameUI->EditStartPos(Vec2(0.f, 1.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pAtlasUI->GetCutInfo().Start.y);
            SetDlgItemText(hDlg, IDC_STARTPOSY, szBuff);
        }
            break;
        case IDC_SLICEX_MINUS:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pAtlasUI->EditEndPos(Vec2(-1.f, 0.f));
            pFrameUI->EditEndPos(Vec2(-1.f, 0.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pAtlasUI->GetCutInfo().End.x - pAtlasUI->GetCutInfo().Start.x);
            SetDlgItemText(hDlg, IDC_SLICESIZEX, szBuff);
        }
            break;
        case IDC_SLICEX_ADD:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pAtlasUI->EditEndPos(Vec2(1.f, 0.f));
            pFrameUI->EditEndPos(Vec2(1.f, 0.f));
            
            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pAtlasUI->GetCutInfo().End.x - pAtlasUI->GetCutInfo().Start.x);
            SetDlgItemText(hDlg, IDC_SLICESIZEX, szBuff);
        }
            break;
        case IDC_SLICEY_MINUS:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pAtlasUI->EditEndPos(Vec2(0.f, -1.f));
            pFrameUI->EditEndPos(Vec2(0.f, -1.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pAtlasUI->GetCutInfo().End.y - pAtlasUI->GetCutInfo().Start.y);
            SetDlgItemText(hDlg, IDC_SLICESIZEY, szBuff);
        }
            break;
        case IDC_SLICEY_ADD:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pAtlasUI->EditEndPos(Vec2(0.f, 1.f));
            pFrameUI->EditEndPos(Vec2(0.f, 1.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pAtlasUI->GetCutInfo().End.y - pAtlasUI->GetCutInfo().Start.y);
            SetDlgItemText(hDlg, IDC_SLICESIZEY, szBuff);
        }
            break;
        case IDC_OFFSETX_MINUS:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pFrameUI->EditOffset(Vec2(-1.f, 0.f));
            
            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameOffset().x);
            SetDlgItemText(hDlg, IDC_OFFSETX, szBuff);
        }
            break;
        case IDC_OFFSETX_ADD:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pFrameUI->EditOffset(Vec2(1.f, 0.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameOffset().x);
            SetDlgItemText(hDlg, IDC_OFFSETX, szBuff);
        }
            break;
        case IDC_OFFSETY_MINUS:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pFrameUI->EditOffset(Vec2(0.f, -1.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameOffset().y);
            SetDlgItemText(hDlg, IDC_OFFSETY, szBuff);
        }
            break;
        case IDC_OFFSETY_ADD:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);

            if (pFrameUI->IsEmpty())
                return (INT_PTR)TRUE;

            pFrameUI->EditOffset(Vec2(0.f, 1.f));

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameOffset().y);
            SetDlgItemText(hDlg, IDC_OFFSETY, szBuff);
        }
            break;
        case IDC_INPUT:
        {
            // 프레임 이미지 출력
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetFrameUI();
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI);
            CUI* pUI2 = pTool->GetAtlasUI();
            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI2);

            Vec2 vOffset = {};
            CUT_INFO Info = pAtlasUI->GetCutInfo();
            
            wchar_t szBuff[256] = {};
            swprintf_s(szBuff, L"%f", Info.Start.x);
            SetDlgItemText(hDlg, IDC_STARTPOSX, szBuff);
            swprintf_s(szBuff, L"%f", Info.Start.y);
            SetDlgItemText(hDlg, IDC_STARTPOSY, szBuff);
            swprintf_s(szBuff, L"%f", Info.End.x - Info.Start.x);
            SetDlgItemText(hDlg, IDC_SLICESIZEX, szBuff);
            swprintf_s(szBuff, L"%f", Info.End.y - Info.Start.y);
            SetDlgItemText(hDlg, IDC_SLICESIZEY, szBuff);
            
            float fDuration = 0.f;
            
            GetDlgItemText(hDlg, IDC_STARTPOSX, szBuff, 256);
            Info.Start.x = (float)_wtof(szBuff);
            GetDlgItemText(hDlg, IDC_STARTPOSY, szBuff, 256);
            Info.Start.y = (float)_wtof(szBuff);
            GetDlgItemText(hDlg, IDC_SLICESIZEX, szBuff, 256);
            Info.End.x = (float)_wtof(szBuff);
            GetDlgItemText(hDlg, IDC_SLICESIZEY, szBuff, 256);
            Info.End.y = (float)_wtof(szBuff);
            GetDlgItemText(hDlg, IDC_OFFSETX, szBuff, 256);
            vOffset.x = (float)_wtof(szBuff);
            GetDlgItemText(hDlg, IDC_OFFSETY, szBuff, 256);
            vOffset.y = (float)_wtof(szBuff);
            GetDlgItemText(hDlg, IDC_DURATION, szBuff, 256);
            fDuration = (float)_wtof(szBuff);

            if (0.f >= fDuration)
            {
                MessageBox(CEngine::GetInst()->GetMainWnd(), L"Duration Error!", L"Error", MB_OK);
                return (INT_PTR)TRUE;
            }
           
           GetDlgItemText(hDlg, IDC_TEXTURENAMEINPUT, szBuff, 256);
           CTexture* pTex = CAssetMgr::GetInst()->FindTexture(szBuff);

           if (nullptr == pTex)
           {
               MessageBox(CEngine::GetInst()->GetMainWnd(), L"Not Find Texture", L"Error", MB_OK);
               return (INT_PTR)TRUE;
           }
           int i = GetDlgItemInt(hDlg, IDC_FRAME, nullptr, true);

           vector<tAnimFrm> frm = pFrameUI->GetVecAnimationFrame();

           if (i > frm.size())
           {
               return (INT_PTR)TRUE;
           }

           pFrameUI->SetFrameInfo(Info, fDuration, vOffset);
           pFrameUI->SetTexture(pTex);
           pFrameUI->ShowFrameImg(i);
        }
            break;
        case IDC_ADDFRAME:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetFrameUI();
            CUI* pUI2 = pTool->GetAtlasUI();
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI);
            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI2);

            pFrameUI->AddCurFrame();
            SetDlgItemInt(hDlg, IDC_FRAME, pFrameUI->GetCurFrame(), true);

            const tAnimFrm& frm = pFrameUI->GetCurFrameInfo();
            wchar_t szBuff[256] = {};
            swprintf_s(szBuff, L"%f", frm.StartPos.x);
            SetDlgItemText(hDlg, IDC_STARTPOSX, szBuff);
            swprintf_s(szBuff, L"%f", frm.StartPos.y);
            SetDlgItemText(hDlg, IDC_STARTPOSY, szBuff);
            swprintf_s(szBuff, L"%f", frm.SliceSize.x);
            SetDlgItemText(hDlg, IDC_SLICESIZEX, szBuff);
            swprintf_s(szBuff, L"%f", frm.SliceSize.y);
            SetDlgItemText(hDlg, IDC_SLICESIZEY, szBuff);
            swprintf_s(szBuff, L"%f", frm.Offset.x);
            SetDlgItemText(hDlg, IDC_OFFSETX, szBuff);
            swprintf_s(szBuff, L"%f", frm.Offset.y);
            SetDlgItemText(hDlg, IDC_OFFSETY, szBuff);
            swprintf_s(szBuff, L"%f", frm.Duration);
            SetDlgItemText(hDlg, IDC_DURATION, szBuff);

            pAtlasUI->SetCutInfo(CUT_INFO(frm.StartPos, Vec2(frm.StartPos.x + frm.SliceSize.x, frm.StartPos.y + frm.SliceSize.y)));
        }
            break; 

        case IDC_MINUSFRAME:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetFrameUI();
            CUI* pUI2 = pTool->GetAtlasUI();
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI);
            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI2);

            pFrameUI->MinusCurFrame();
            SetDlgItemInt(hDlg, IDC_FRAME, pFrameUI->GetCurFrame(), true);

            const tAnimFrm& frm = pFrameUI->GetCurFrameInfo();
            wchar_t szBuff[256] = {};
            swprintf_s(szBuff, L"%f", frm.StartPos.x);
            SetDlgItemText(hDlg, IDC_STARTPOSX, szBuff);
            swprintf_s(szBuff, L"%f", frm.StartPos.y);
            SetDlgItemText(hDlg, IDC_STARTPOSY, szBuff);
            swprintf_s(szBuff, L"%f", frm.SliceSize.x);
            SetDlgItemText(hDlg, IDC_SLICESIZEX, szBuff);
            swprintf_s(szBuff, L"%f", frm.SliceSize.y);
            SetDlgItemText(hDlg, IDC_SLICESIZEY, szBuff);
            swprintf_s(szBuff, L"%f", frm.Offset.x);
            SetDlgItemText(hDlg, IDC_OFFSETX, szBuff);
            swprintf_s(szBuff, L"%f", frm.Offset.y);
            SetDlgItemText(hDlg, IDC_OFFSETY, szBuff);
            swprintf_s(szBuff, L"%f", frm.Duration);
            SetDlgItemText(hDlg, IDC_DURATION, szBuff);

            pAtlasUI->SetCutInfo(CUT_INFO(frm.StartPos, Vec2(frm.StartPos.x + frm.SliceSize.x, frm.StartPos.y + frm.SliceSize.y)));
        }
            break;

        case IDC_ADDMAXFRAME:
        {
           CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
           CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
           CUI* pUI = pTool->GetFrameUI();
           CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI);
          
           pFrameUI->AddMaxFrame();
           SetDlgItemInt(hDlg, IDC_MAXFRAME, pFrameUI->GetMaxFrame(), true);      
        }
            break;

        case IDC_ANIMATIONSAVE:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAnimationUI();
            CAnimationUI* pAnimUI = dynamic_cast<CAnimationUI*>(pUI);
            CUI* pUI2 = pTool->GetAtlasUI();
            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI2);
            wchar_t szBuff[256] = {};
            CUI* pUI3 = pTool->GetFrameUI();
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI3);

            GetDlgItemText(hDlg, IDC_ANIMATIONNAMEINPUT, szBuff, 256);
            
            pAnimUI->CreateAnimation(szBuff, pFrameUI->GetVecAnimationFrame(), pAtlasUI->GetAtlasTexture());
            pAtlasUI->Reset();
            
            swprintf_s(szBuff, L"");
            SetDlgItemText(hDlg, IDC_TEXTURENAMEINPUT, szBuff);
            SetDlgItemText(hDlg, IDC_ANIMATIONNAMEINPUT, szBuff);
            SetDlgItemText(hDlg, IDC_STARTPOSX, L"0");
            SetDlgItemText(hDlg, IDC_STARTPOSY, L"0");
            SetDlgItemText(hDlg, IDC_SLICESIZEX, L"0");
            SetDlgItemText(hDlg, IDC_SLICESIZEY, L"0");
            SetDlgItemText(hDlg, IDC_OFFSETX, L"0");
            SetDlgItemText(hDlg, IDC_OFFSETY, L"0");
            SetDlgItemText(hDlg, IDC_DURATION, L"0");
            SetDlgItemInt(hDlg, IDC_MAXFRAME, 0, true);
            SetDlgItemInt(hDlg, IDC_FRAME, 0, true);
        }
            break;
        case IDC_PLAYANIMATION:
        {
            wchar_t szBuff[256] = {};
            GetDlgItemText(hDlg, IDC_ANIMATIONNAMEINPUT, szBuff, 256);
            
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAnimationUI();
            CAnimationUI* pAnimUI = dynamic_cast<CAnimationUI*>(pUI);

            pAnimUI->PlayAnimation(szBuff, false);
        }
            break;
        case IDC_CUTTING:
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            CUI* pUI = pTool->GetAtlasUI();
            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            
            pAtlasUI->SetMouseClicekd(true);
        }
            break;
        case IDC_TEXTURESELECT:
            DialogBoxParam(CEngine::GetInst()->GetProcessInstance(), MAKEINTRESOURCE(IDD_TEXTURE_NAME), CEngine::GetInst()->GetMainWnd(), TextureSelectProc, (LPARAM)hDlg);
            break;
        case IDC_ANIMATIONSELECT:
            DialogBoxParam(CEngine::GetInst()->GetProcessInstance(), MAKEINTRESOURCE(IDD_ANIMATION_NAME), CEngine::GetInst()->GetMainWnd(), AnimationSelectProc, (LPARAM)hDlg);
            break;
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDEXIT:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
    }
         return (INT_PTR)TRUE;
         break;
    }
    return (INT_PTR)FALSE;
}

HWND hPrevDlg = nullptr;

INT_PTR CALLBACK TextureSelectProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
        CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
        
        CUI* pUI = pTool->GetAtlasUI();
        CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
        const vector<CTexture*> vecTex = pAtlasUI->GetVecTexture();
        HWND hListBox = GetDlgItem(hDlg, IDC_TEXTUREMENU);
        hPrevDlg = (HWND)lParam;
        for (size_t i = 0; i < vecTex.size(); ++i)
        {
            int pos = (int)SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)vecTex[i]->GetKey().c_str());
            SendMessage(hListBox, LB_SETITEMDATA, pos, (LPARAM)i);
        }
        SetFocus(hListBox);
        return TRUE;
    }
    return (INT_PTR)TRUE;
    break;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            HWND hListBox = GetDlgItem(hDlg, IDC_TEXTUREMENU);
            int selected = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            wchar_t selectedText[MAX_PATH] = {};
            SendMessage(hListBox, LB_GETTEXT, selected, (LPARAM)selectedText);

            if (selected != LB_ERR)
            {
                if (hPrevDlg != nullptr) // 여기서 hPrevDlg를 사용합니다.
                {
                    CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
                    
                    SetDlgItemText(hPrevDlg, IDC_TEXTURENAMEINPUT, selectedText);
                }
            }
            // 조건에 관계없이 대화상자를 종료합니다.
            CUI* pUI = pTool->GetAtlasUI();
            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            pAtlasUI->SetAtlasTexture(selectedText);
            assert(pTool);

            EndDialog(hDlg, IDOK);
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, IDEXIT);
            return (INT_PTR)TRUE;
        }

        else if (LOWORD(wParam) == IDEXIT)
        {
            EndDialog(hDlg, IDEXIT);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AnimationSelectProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_INITDIALOG:
    {
        CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
        CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
        CUI* pUI = pTool->GetAnimationUI();
        CAnimationUI* pAnimationUI = dynamic_cast<CAnimationUI*>(pUI);
        CAnimator* pAnimator = pAnimationUI->GetAnimator();
        hPrevDlg = (HWND)lParam;
        map<wstring, CAnimation*> mapAnim = pAnimator->GetAnimationmap();
        
        map<wstring, CAnimation*>::iterator iter = mapAnim.begin();
        
        int i = 0;
        for (; iter != mapAnim.end(); ++iter)
        {
            HWND hListBox = GetDlgItem(hDlg, IDC_ANIMATIONMENU);
            int pos = (int)SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)iter->first.c_str());
            SendMessage(hListBox, LB_SETITEMDATA, pos, (LPARAM)i);
            ++i;
        }
        
    }
    return (INT_PTR)TRUE;
    break;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
            CLevel_AnimTool* pTool = dynamic_cast<CLevel_AnimTool*>(pLevel);
            HWND hListBox = GetDlgItem(hDlg, IDC_ANIMATIONMENU);
            int selected = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            wchar_t selectedText[MAX_PATH] = {};
            SendMessage(hListBox, LB_GETTEXT, selected, (LPARAM)selectedText);

            if (selected != LB_ERR)
            {
                if (hPrevDlg != nullptr)
                {
                    SetDlgItemText(hPrevDlg, IDC_ANIMATIONNAMEINPUT, selectedText);
                }
            }
            
            CUI* pUI = pTool->GetAtlasUI();
            CUI* pUI2 = pTool->GetFrameUI();
            CUI* pUI3 = pTool->GetAnimationUI();

            CAtlasUI* pAtlasUI = dynamic_cast<CAtlasUI*>(pUI);
            CFrameUI* pFrameUI = dynamic_cast<CFrameUI*>(pUI2);
            CAnimationUI* pAnimationUI = dynamic_cast<CAnimationUI*>(pUI3);
            
            pAtlasUI->Reset();
            pFrameUI->Reset();
            pAnimationUI->Reset();

            pAnimationUI->InitAnimation(selectedText);
            CAnimator* pAnimator = pAnimationUI->GetAnimator();
            pFrameUI->InitFrame(selectedText, pAnimator->GetCurAnim()->GetImg());
            const tAnimFrm& frm = pFrameUI->GetCurFrameInfo();
            Vec2 StartPos = frm.StartPos;
            Vec2 SliceSize = frm.SliceSize;

            CUT_INFO info = {};
            info.Start = frm.StartPos;
            info.End = StartPos + SliceSize;
            pAtlasUI->Init(pAnimator->GetCurAnim()->GetImg(), info);

            wchar_t szBuff[256] = {};

            swprintf_s(szBuff, L"%s", pAtlasUI->GetAtlasTexture()->GetKey().c_str());
            SetDlgItemText(hPrevDlg, IDC_TEXTURENAMEINPUT, szBuff);
            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().StartPos.x);
            SetDlgItemText(hPrevDlg, IDC_STARTPOSX, szBuff);
            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().StartPos.y);
            SetDlgItemText(hPrevDlg, IDC_STARTPOSY, szBuff);
            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().SliceSize.x);
            SetDlgItemText(hPrevDlg, IDC_SLICESIZEX, szBuff);
            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().SliceSize.y);
            SetDlgItemText(hPrevDlg, IDC_SLICESIZEY, szBuff);
            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().Offset.x);
            SetDlgItemText(hPrevDlg, IDC_OFFSETX, szBuff);
            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().Offset.y);
            SetDlgItemText(hPrevDlg, IDC_OFFSETY, szBuff);
            swprintf_s(szBuff, L"%f", pFrameUI->GetCurFrameInfo().Duration);
            SetDlgItemText(hPrevDlg, IDC_DURATION, szBuff);
            SetDlgItemInt(hPrevDlg, IDC_MAXFRAME, pFrameUI->GetMaxFrame(), true);
            SetDlgItemInt(hPrevDlg, IDC_FRAME, pFrameUI->GetCurFrame(), true);

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }

        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}