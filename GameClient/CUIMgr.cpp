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
	vector<CObj*>& vecUI = pCurLevel->m_arrObj[(UINT)LAYER_TYPE::UI];

	// �켱������ ���� ���� �θ� UI�� �ּҸ� �ޱ����� ����
	CUI* pFocusedUI = nullptr;
	// ���� �켱������ ���� �θ� UI ���� �켱������ ���� ������
	// ���콺�� �ö��ִ��� Ȯ���Ѵ�.

	vector<CObj*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		CUI* pParent = (CUI*)(*iter);

		if (pParent->IsMouseOn())
		{
			pFocusedUI = pParent;
		}
	}

	// ���콺�� � UI�� ��Ŀ�� �ϰ� ���� �ʴٸ� return
	if (nullptr == pFocusedUI)
		return;

	// �θ� UI�� �����ؼ� �ڽ� ����, �� �߿��� �� �켱���찡 ���� UI �� ã�Ƴ���.
	CUI* pPriorityUI = GetPriorityUI(pFocusedUI);
	assert(pPriorityUI);

	// ���� ��ư�� ���Ȱ� �װ� �ش� UI�� �ȿ��� ���
	if (LBtnTap)
	{
		// ���� ��ư ���� ȣ��
		pPriorityUI->LButtonDown();

		// ������ �߻��ϸ� �ش� UI�� ��Ŀ�̵� UI �� ����ó�� �Ѵ�.
		ChangeFocusedUI(pPriorityUI);
	}
	// ���� ��ư�� ������, �װ� �ش� UI �ȿ�����
	else if (LBtnReleased)
	{
		// ���� ��ư �� ȣ��
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
	
	// queue�� ������� ���� ���� ��� �ݺ�
	while (!queue.empty())
	{
		// queue�� front�� �޾ƿͼ� queue�� front�� ����������.
		CUI* pUI = queue.front();
		queue.pop_front();

		// �ش� UI�� ���콺On ���¶��
		if (pUI->IsMouseOn())
		{
			// ���� ��Ŀ���� UI�� �������ְ�
			pPriorityUI = pUI;

			// �ش� UI�� �ڽ� UI�鿡 ���� �����ؼ� queue�� �־��ش�.
			// ������ queue�� �����ִ� �ش� UI�� ��Ŀ���� UI��.
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
	// ��Ŀ�̵� UI �� �ٽ� ������ ���, ���ٸ� �۾��� ���� �ʴ´�.
	if (m_FocusedUI == _UI)
		return;

	// ��Ŀ�̵� UI�� ����Ǿ����� ��ü��Ų��.
	m_FocusedUI = _UI;

	// �������� ���Ӱ� ��Ŀ�̵� UI�� ã�Ƽ� vector �� �ڷ� ������.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	// ���� Level�� nullptr�̸� return
	if (nullptr == pCurLevel)
		return;

	vector<CObj*>& vecUI = pCurLevel->m_arrObj[(UINT)LAYER_TYPE::UI];
	vector<CObj*>::iterator iter = vecUI.begin();

	// UI�� end���� ��ȸ�Ѵ�.
	for (; iter != vecUI.end(); ++iter)
	{
		// ��Ŀ�̵� UI�� iterator�� ������ iterator�� erase�ϰ� �ش� ��Ŀ�� UI�� push_back �ؼ� ���� �ڷ� �־��ְ� break ó�� �ع�����.
		if ((*iter) == _UI)
		{
			vecUI.erase(iter);
			vecUI.push_back(_UI);
			break;
		}
	}
}