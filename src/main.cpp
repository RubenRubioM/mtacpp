#include "mta.h"

#include <chrono>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

int main()
{
    mta::Timer timer;
    timer.start();
    std::cout << "sizeof(Timer): " << sizeof(mta::Timer<>) << " bytes\n";
    std::this_thread::sleep_for(1s);
    std::cout << "As Duration: " << timer.elapsedAsDuration<mta::DecimalNanoseconds>() << '\n';
    std::cout << "As count(): " << timer.elapsed<mta::DecimalNanoseconds>() << '\n';
    std::cout << timer.isStopped() << '\n';
    timer.stop();
    std::cout << "Timer Stopped\n";
    std::cout << timer.isStopped() << '\n';
    std::this_thread::sleep_for(1s);
    std::cout << "As Duration: " << timer.elapsedAsDuration<mta::DecimalNanoseconds>() << '\n';
    std::cout << "As count(): " << timer.elapsed<mta::DecimalNanoseconds>() << '\n';
}