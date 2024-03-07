#include "pch.h"
#include "CLevel_Editor.h"
#include "CKeyMgr.h"

CLevel_Editor::CLevel_Editor()
{
}

CLevel_Editor::~CLevel_Editor()
{
}

void CLevel_Editor::begin()
{
}

void CLevel_Editor::tick()
{
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CLevel_Editor::Enter()
{
}

void CLevel_Editor::Exit()
{
	DeleteAllObjects();
}