#ifndef COMMON_TIMER_H
#define COMMON_TIMER_H

#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

namespace COMMON
{
    class Common_Timer
    {
        private:
            uint32_t time_to_expired_second;
            std::condition_variable m_ConditionVar;
            std::thread *m_Thread;
            std::function<void()> m_OneExpiredHandler;

        public:
            Common_Timer(uint32_t seconds);
            virtual ~Common_Timer();

            virtual void Start(std::function<void()> OnTimerExpired);
            virtual void SetTimeToExpiried(const uint32_t& time);
            virtual void Stop();
            virtual void WaitFunc();

        protected:

        private:
    };
}
#endif // COMMON_TIMER_H
