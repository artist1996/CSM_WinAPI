#pragma once
#include "CState_Boss.h"
class CBoss_Destroy :
    public CState_Boss
{
private:
    CSound* m_pSound;
    CSound* m_pSound2;
    float   m_DestroyTime;
    float   m_Time;
    float   m_SoundTime;

    bool    m_CameraEvent;
    
    

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CBoss_Destroy);
    CBoss_Destroy();
    virtual ~CBoss_Destroy();
};

