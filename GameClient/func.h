#pragma once


void DrawDebugRect(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time);
void DrawDebugCircle(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time);
void DebugLog(LOG_TYPE _Type, const wchar_t* _LogMgs);


template<typename T1, typename T2>
void Safe_Del_Map(map<T1, T2>& _map)
{
	for (const auto& pair : _map)
	{
		if(nullptr != pair.second)
			delete pair.second;
	}

	_map.clear();
}


template<typename T>
void Safe_Del_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}

template<typename T, UINT iSize>
void Safe_Del_Arr(T* (&Arr)[iSize])
{
	for (UINT i = 0; i < iSize; ++i)
	{
		if (nullptr != Arr[i])
		{
			delete Arr[i];
			Arr[i] = nullptr;
		}		
	}
}

float Saturate(float _Ratio);


class CObj;
class CLevel;

bool IsValid(CObj*& _Object);


// =============
// Task ���� �Լ�
// =============
void SpawnObject(CLevel* _Level, LAYER_TYPE _type, CObj* _pSpawned);
