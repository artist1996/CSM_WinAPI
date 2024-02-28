#pragma once
#include "CComponent.h"

enum class DATA_TYPE
{
    INT,
    FLOAT,
    VEC2,
    OBJECT,
};

struct tBlackboardData
{
    DATA_TYPE Type;
    void*     pData;
};

// FSM (Finite State Machine)
class CState;

class CFSM :
    public CComponent
{ 
private:
    static map<wstring, tBlackboardData> m_mapGlobalData;      // ���� ������

private:
    map<wstring, tBlackboardData>        m_mapData;            // �� ��ü�� ������ ������
    map<wstring, CState*>                m_mapState;           // ���µ�
    CState*                              m_CurState;           // ���� ����

public:
    void AddState(const wstring& _strStateName, CState* _State);
    CState* FindState(const wstring& _strStateName);
    void ChangeState(const wstring& _strNextStateName);

public:
    virtual void finaltick() override;

public:
    CLONE(CFSM);
    CFSM();
    ~CFSM();
};

