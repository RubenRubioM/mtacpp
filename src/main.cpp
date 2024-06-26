#include "mta.h"

#include <chrono>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

int main()
{
    mta::Timer timer;
    timer.start();
    std::this_thread::sleep_for(1s);
    std::cout << "As Duration: " << timer.elapsedAsDuration<mta::DecimalSeconds>() << '\n';
    std::cout << "As count(): " << timer.elapsed<mta::IntegerSeconds>() << '\n';
}