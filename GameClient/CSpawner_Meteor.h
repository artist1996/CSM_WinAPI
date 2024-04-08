#pragma once
#include "CObj.h"

class CSpawner_Meteor :
    public CObj
{
private:
    CObj*   m_Owner;
    OBJ_ID  m_ID;

    float   m_Time;
    bool    m_Spawn;

public:
    virtual void tick() override;


public:
    CLONE(CSpawner_Meteor);
    CSpawner_Meteor();
    CSpawner_Meteor(CObj* _Owner, OBJ_ID _ID);
    virtual ~CSpawner_Meteor();
};

