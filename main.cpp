#include <iostream>
#include <functional>
#include <chrono>

#include "Common_Timer.h"


using namespace std;

bool isEnd = false;

void OnTimerExpiredandle_cb()
{
    std::cout << "Entering function: " << __func__ << std::endl;
    std::cout << "Handling..." << std::endl;
    isEnd = true;
    std::cout << "Leaving function: " << __func__ << std::endl;

}

int main()
{
    std::cout << "Entering function: " << __func__ << std::endl;
    uint32_t counting = 0;
    COMMON::Common_Timer *timerIns = new COMMON::Common_Timer(5);
    //COMMON::Common_Timer *timerIns_2 = new COMMON::Common_Timer(10);

    timerIns->Start(std::bind(&OnTimerExpiredandle_cb));
    //timerIns_2->Start(std::bind(&OnTimerExpiredandle_cb));

    while(!isEnd)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << ++counting << " ";
        //timerIns->Stop();

    }
    timerIns->Stop();
    delete timerIns;
    //delete timerIns_2;

    std::cout <<"\n";
    std::cout << "Leaving function: " << __func__ << std::endl;
    return 0;
}
