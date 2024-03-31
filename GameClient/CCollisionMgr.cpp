#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CRigidBody.h"

CCollisionMgr::CCollisionMgr()
	: m_Matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}


void CCollisionMgr::init()
{

}

void CCollisionMgr::tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (int Row = 0; Row < (UINT)LAYER_TYPE::END; ++Row)
	{
		for (int Col = Row; Col < (UINT)LAYER_TYPE::END; ++Col)
		{
			if (m_Matrix[Row] & (1 << Col))
			{
				const vector<CCollider*>& vecLeft = pCurLevel->GetColliders((LAYER_TYPE)Row);
				const vector<CCollider*>& vecRight = pCurLevel->GetColliders((LAYER_TYPE)Col);

				for (size_t i = 0; i < vecLeft.size(); ++i)
				{
					for (size_t j = 0; j < vecRight.size(); ++j)
					{
						COLLIDER_ID id = {};

						id.LeftID = vecLeft[i]->GetID();
						id.RightID = vecRight[j]->GetID();

						map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(id.ID);

						// ��ϵ����� ������ ��Ͻ�Ų��.
						if (iter == m_mapCollisionInfo.end())
						{
							m_mapCollisionInfo.insert(make_pair(id.ID, false));
							iter = m_mapCollisionInfo.find(id.ID);
						}

						bool bDead = vecLeft[i]->GetOwner()->IsDead() || vecRight[j]->GetOwner()->IsDead();
						bool bDeactive = !vecLeft[i]->IsActive() || !vecRight[j]->IsActive();


						// �� �浹ü�� ���� �浹���̴�.
						if (IsCollision(vecLeft[i], vecRight[j]))
						{
							// �������� �浹���̾���.
							if (iter->second)
							{
								vecLeft[i]->OnOverlap(vecRight[j]);
								vecRight[j]->OnOverlap(vecLeft[i]);								
							}

							// �������� �浹���� �ƴϾ���.
							else
							{
								vecLeft[i]->BeginOverlap(vecRight[j]);
								vecRight[j]->BeginOverlap(vecLeft[i]);
							}

							iter->second = true;

							// �� �浹ü�� �ϳ��� Dead ���°ų� ��Ȱ��ȭ ���¶��
							// �߰��� �浹 ������ ȣ������ش�.
							if (bDead || bDeactive)
							{
								vecLeft[i]->EndOverlap(vecRight[j]);
								vecRight[j]->EndOverlap(vecLeft[i]);
								iter->second = false;
							}
						}

						// �� �浹ü�� ���� �浹���� �ƴϴ�.
						else
						{
							// �������� �浹���̾���.
							if (iter->second)
							{
								vecLeft[i]->EndOverlap(vecRight[j]);
								vecRight[j]->EndOverlap(vecLeft[i]);
							}

							iter->second = false;
						}
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionCheck(LAYER_TYPE Layer1, LAYER_TYPE Layer2)
{
	UINT Row = (UINT)Layer1;
	UINT Col = (UINT)Layer2;

	if (Row > Col)
	{
		Row = (UINT)Layer2;
		Col = (UINT)Layer1;
	}

	m_Matrix[Row] |= (1 << Col);
}


void CCollisionMgr::CollisionUnCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	UINT Row = (UINT)_Layer1;
	UINT Col = (UINT)_Layer2;

	if (Row > Col)
	{
		Row = (UINT)_Layer2;
		Col = (UINT)_Layer1;
	}

	m_Matrix[Row] &= ~(1 << Col);
}

bool CCollisionMgr::IsCollision(CCollider* _Left, CCollider* _Right)
{
	Vec2 vLeftPos = _Left->GetFinalPos();
	Vec2 vLeftScale = _Left->GetScale();

	Vec2 vRightPos = _Right->GetFinalPos();
	Vec2 vRightScale = _Right->GetScale();

	if (_Left->GetOwner()->GetLayerType() == LAYER_TYPE::LINE)
	{
		Vec2 vLeftLinePos = _Left->GetOwner()->GetPos();
		Vec2 vRightLinePos = _Left->GetOwner()->GetScale();
		Vec2 vPlayerPos = _Right->GetOwner()->GetPos();
		Vec2 vPlayerScale = _Right->GetOwner()->GetScale();
		if (vPlayerPos.x >= vLeftLinePos.x && vPlayerPos.x <= vRightLinePos.x)
		{
			float M = 0.f;
			float B = 0.f;

			M = (vRightLinePos.y - vLeftLinePos.y) / (vRightLinePos.x - vLeftLinePos.x);

			B = vLeftLinePos.y - (M * vLeftLinePos.x);

			float LineY = M * vPlayerPos.x + B;

			if (vPlayerPos.y >= LineY - 10.f)
			{
				return true;
			}
		}
		return false;
	}

	else
	{
		if (abs(vLeftPos.x - vRightPos.x) <= (vLeftScale.x + vRightScale.x) * 0.5f
			&& abs(vLeftPos.y - vRightPos.y) <= (vLeftScale.y + vRightScale.y) * 0.5f)
		{
			return true;
		}
	}

	return false;
}
