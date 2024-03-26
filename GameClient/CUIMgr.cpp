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
	vector<CObj*>& vecUI = pCurLevel->m_arrObj[(UINT)LAYER_TYPE::UI];

	// 우선순위가 가장 높은 부모 UI의 주소를 받기위한 변수
	CUI* pFocusedUI = nullptr;
	// 제일 우선순위가 낮은 부모 UI 부터 우선순위가 높은 순서로
	// 마우스가 올라가있는지 확인한다.

	vector<CObj*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		CUI* pParent = (CUI*)(*iter);

		if (pParent->IsMouseOn())
		{
			pFocusedUI = pParent;
		}
	}

	// 마우스가 어떤 UI도 포커스 하고 있지 않다면 return
	if (nullptr == pFocusedUI)
		return;

	// 부모 UI를 포함해서 자식 까지, 이 중에서 더 우선순우가 높은 UI 를 찾아낸다.
	CUI* pPriorityUI = GetPriorityUI(pFocusedUI);
	assert(pPriorityUI);

	// 왼쪽 버튼이 눌렸고 그게 해당 UI의 안에서 라면
	if (LBtnTap)
	{
		// 왼쪽 버튼 눌림 호출
		pPriorityUI->LButtonDown();

		// 눌림이 발생하면 해당 UI를 포커싱된 UI 로 변경처리 한다.
		ChangeFocusedUI(pPriorityUI);
	}
	// 왼쪽 버튼이 떼졌고, 그게 해당 UI 안에서면
	else if (LBtnReleased)
	{
		// 왼쪽 버튼 뗌 호출
		pPriorityUI->LButtonUp();

		if (pPriorityUI->IsLbtnDowned())
		{
			pPriorityUI->LButtonClicked();
		}
	}
}

CUI* CUIMgr::GetPriorityUI(CUI* _UI)
{
	static list<CUI*> queue;
	queue.clear();
	
	CUI* pPriorityUI = nullptr;

	queue.push_back(_UI);
	
	// queue가 비어있지 않을 동안 계속 반복
	while (!queue.empty())
	{
		// queue의 front를 받아와서 queue의 front를 지워버린다.
		CUI* pUI = queue.front();
		queue.pop_front();

		// 해당 UI가 마우스On 상태라면
		if (pUI->IsMouseOn())
		{
			// 현재 포커스된 UI로 변경해주고
			pPriorityUI = pUI;

			// 해당 UI의 자식 UI들에 전부 접근해서 queue에 넣어준다.
			// 마지막 queue에 남아있는 해당 UI가 포커스된 UI다.
			const vector<CUI*>& vecChildUI = pUI->GetChildUI();
			for (size_t i = 0; i < vecChildUI.size(); ++i)
			{
				queue.push_back(vecChildUI[i]);
			}
		}
	}
	
	return pPriorityUI;
}

void CUIMgr::ChangeFocusedUI(CUI* _UI)
{
	// 포커싱된 UI 를 다시 조작한 경우, 별다른 작업을 하지 않는다.
	if (m_FocusedUI == _UI)
		return;

	// 포커싱된 UI가 변경되었으면 교체시킨다.
	m_FocusedUI = _UI;

	// 레벨에서 새롭게 포커싱된 UI를 찾아서 vector 맨 뒤로 보낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	// 현재 Level이 nullptr이면 return
	if (nullptr == pCurLevel)
		return;

	vector<CObj*>& vecUI = pCurLevel->m_arrObj[(UINT)LAYER_TYPE::UI];
	vector<CObj*>::iterator iter = vecUI.begin();

	// UI의 end까지 순회한다.
	for (; iter != vecUI.end(); ++iter)
	{
		// 포커싱된 UI가 iterator와 같으면 iterator를 erase하고 해당 포커싱 UI를 push_back 해서 제일 뒤로 넣어주고 break 처리 해버린다.
		if ((*iter) == _UI)
		{
			vecUI.erase(iter);
			vecUI.push_back(_UI);
			break;
		}
	}
}