#include <iostream>

#include "Common_Timer.h"

using namespace COMMON;

Common_Timer::Common_Timer(uint32_t seconds)
{
    std::cout << "Entering function: " << __func__ << std::endl;
    time_to_expired_second = seconds;
    std::cout << "Leaving function: " << __func__ << std::endl;
}

Common_Timer::~Common_Timer()
{
    std::cout << "Entering function: " << __func__ << std::endl;
    m_ConditionVar.notify_all();
    if(m_Thread->joinable())
    {
        m_Thread->detach();
    }
    std::cout << "Leaving function: " << __func__ << std::endl;
}

void Common_Timer::Start(std::function<void()>OnTimerExpired)
{
    std::cout << "Entering function: " << __func__ << std::endl;
    m_OneExpiredHandler = OnTimerExpired;
    //m_ConditionVar.notify_all();
    m_Thread = new std::thread(&Common_Timer::WaitFunc,this);
    if(m_Thread->joinable())
    {
        m_Thread->detach();
    }

    //VFX_QLOGW("TIMER"," Timer %d seconds started",time_to_expired_second);
    std::cout << "Timer " << time_to_expired_second << " seconds started" << std::endl;
    std::cout << "Leaving function: " << __func__ << std::endl;
}

void Common_Timer::SetTimeToExpiried(const uint32_t& time)
{
    std::cout << "Entering function: " << __func__ << std::endl;
    time_to_expired_second = time;
    std::cout << "Leaving function: " << __func__ << std::endl;
}

void Common_Timer::Stop()
{
    std::cout << "Entering function: " << __func__ << std::endl;
    m_ConditionVar.notify_all();
//    if(m_Thread->joinable())
//    {
//        m_Thread->detach();
//    }
    //VFX_QLOGI("TIMER"," Timer %d seconds stopped",time_to_expired_second);
    std::cout << "Timer " << time_to_expired_second << " seconds stopped" << std::endl;
    std::cout << "Leaving function: " << __func__ << std::endl;
}

void Common_Timer::WaitFunc()
{
    std::cout << "Entering function: " << __func__ << std::endl;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);
    if((m_ConditionVar.wait_for(lck,std::chrono::seconds(time_to_expired_second)) == std::cv_status::timeout))
    {
        m_OneExpiredHandler();
    }
    else
    {
        //VFX_QLOGI("TIMER"," Event Received...! Timer %d seconds stopped");
        std::cout << "Event Received...! Timer " << time_to_expired_second << " seconds stopped" << std::endl;
    }
    std::cout << "Leaving function: " << __func__ << std::endl;
}
