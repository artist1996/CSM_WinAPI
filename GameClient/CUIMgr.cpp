#include "pch.h"
#include "CUIMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CUI.h"

CUIMgr::CUIMgr()
{}

CUIMgr::~CUIMgr()
{}

void CUIMgr::tick()
{
	bool LBtnTap = KEY_TAP(KEY::LBTN);
	bool LBtnReleased = KEY_RELEASED(KEY::LBTN);
	
	// 현재 레벨에 등록된 UI들의 이벤트를 처리한다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// UI로 강제 캐스팅해준다. 조심할 것!
		CUI* pUI = (CUI*)vecUI[i];

		// 왼쪽 버튼이 눌렸고 해당 UI 안에서면
		if (LBtnTap && pUI->IsMouseOn())
		{
			// 왼쪽 버튼 눌림 호출
			pUI->LButtonDown();
		}
		// 왼쪽 버튼이 떼졌고 해당 UI 안에서면
		else if (LBtnReleased && pUI->IsMouseOn())
		{
			// 왼쪽 버튼 뗌 호출
			pUI->LButtonUp();

			// 이전 프레임에 누른적이 있다면
			if (pUI->IsMouseOnPrev())
			{
				// 왼쪽 버튼 클릭 호출
				pUI->LButtonClicked();
			}
		}
	}
}
