#include "pch.h"
#include "CDbgRender.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"


CDbgRender::CDbgRender()
	: m_bRender(true)
	, m_LogLife(3.5f)
	, m_LogSpace(18)
	, m_LogStartPos(Vec2(10.f, 10.f))
{
}

CDbgRender::~CDbgRender()
{
}

void CDbgRender::tick()
{
	if (KEY_TAP(KEY::_0))
	{
		m_bRender ? m_bRender = false : m_bRender = true;
	}
}

void CDbgRender::render()
{
	list<tDbgRenderInfo>::iterator iter = m_RenderList.begin();

	for (; iter != m_RenderList.end(); )
	{
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);
		CSelectObj SelectPen(DC, CEngine::GetInst()->GetPen(iter->Color));
		
		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(iter->Position);

		// DBG 가 Rect 면 사각형을 그린다.
		if (m_bRender && DBG_SHAPE::RECT == iter->Shape)
		{
			Rectangle(DC
				, (int)(vRenderPos.x - iter->Scale.x / 2.f)
				, (int)(vRenderPos.y - iter->Scale.y / 2.f)
				, (int)(vRenderPos.x + iter->Scale.x / 2.f)
				, (int)(vRenderPos.y + iter->Scale.y / 2.f));
		}
		 
		// DBG_SHAPE 가 Circle 이면 원을 그린다.
		else if(m_bRender && DBG_SHAPE::CIRCLE == iter->Shape)
		{
			Ellipse(DC
				, (int)(vRenderPos.x - iter->Scale.x / 2.f)
				, (int)(vRenderPos.y - iter->Scale.y / 2.f)
				, (int)(vRenderPos.x + iter->Scale.x / 2.f)
				, (int)(vRenderPos.y + iter->Scale.y / 2.f));
		}

		// 해당 디버그렌더 정보가 수명을 다하면 리스트에서 제거한다.
		(*iter).Age += DT;
		if (iter->Duration < iter->Age)
		{
			iter = m_RenderList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// 로그정보 출력
	list<tDbgLog>::iterator logiter = m_LogList.begin();

	SetBkMode(DC, TRANSPARENT);

	int i = 0;
	for (; logiter != m_LogList.end(); )
	{	
		if (m_bRender)
		{
			// 오래된 로그일 수록 아래쪽에 출력이 되야함.
			// 로그의 y 축 Offset 위치를 구함
			int yoffset = ((int)m_LogList.size() - (i + 1)) * m_LogSpace;

			switch (logiter->Type)
			{
			case LOG_TYPE::DBG_LOG:
				SetTextColor(DC, RGB(255, 255, 255));
				break;
			case LOG_TYPE::DBG_WARNING:
				SetTextColor(DC, RGB(240, 240, 20));
				break;
			case LOG_TYPE::DBG_ERROR:
				SetTextColor(DC, RGB(240, 20, 20));
				break;
			}

			TextOut(DC, (int)m_LogStartPos.x
				, (int)m_LogStartPos.y + yoffset
				, logiter->strLog.c_str()
				, (int)logiter->strLog.length());
		}
		
				
		// 로그 나이 계산
		logiter->Age += DT;

		// 수명이 넘은 로그는 삭제
		if (m_LogLife <= logiter->Age)
		{
			logiter = m_LogList.erase(logiter);
		}
		else
		{
			++logiter;
		}

		++i;
	}

	SetBkMode(DC, OPAQUE);
	SetTextColor(DC, RGB(0, 0, 0));
}
