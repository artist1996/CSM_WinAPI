#pragma once


#include <Windows.h>
#include <vector>	// �����迭
#include <list>		// ������ ����Ʈ
#include <map>		// ����Ž��Ʈ��
#include <string>   // ���ڿ� ���� ���� 
#include <assert.h>

// TransparentBlt �� �����Ǿ��ִ� ���̺귯�� ��ũ
#pragma comment(lib, "Msimg32.lib")




using std::vector;
using std::list;
using std::map;
using std::make_pair;

using std::string;
using std::wstring;

#include "define.h"
#include "enum.h"
#include "struct.h"
#include "func.h"

#include "CSelectObj.h"

// png �ε� ���� �߰�
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;