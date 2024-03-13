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
	
	// ���� ������ ��ϵ� UI���� �̺�Ʈ�� ó���Ѵ�.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// UI�� ���� ĳ�������ش�. ������ ��!
		CUI* pUI = (CUI*)vecUI[i];

		// ���� ��ư�� ���Ȱ� �ش� UI �ȿ�����
		if (LBtnTap && pUI->IsMouseOn())
		{
			// ���� ��ư ���� ȣ��
			pUI->LButtonDown();
		}
		// ���� ��ư�� ������ �ش� UI �ȿ�����
		else if (LBtnReleased && pUI->IsMouseOn())
		{
			// ���� ��ư �� ȣ��
			pUI->LButtonUp();

			// ���� �����ӿ� �������� �ִٸ�
			if (pUI->IsMouseOnPrev())
			{
				// ���� ��ư Ŭ�� ȣ��
				pUI->LButtonClicked();
			}
		}
	}
}
