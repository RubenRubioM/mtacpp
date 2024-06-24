#include "mta.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <format>
#include <printf.h>

int main()
{
    mta::Timer<std::chrono::milliseconds> timer;
    timer.start();
    // std::chrono::time_point tp = std::chrono::high_resolution_clock::now();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // std::chrono::time_point tp2 = std::chrono::high_resolution_clock::now();
    // std::chrono::duration d = std::chrono::duration<double, std::ratio<60>>(tp2 - tp);
    // std::cout << "Duration: " << d << '\n';
    std::cout << "As Duration: " << timer.elapsedAsDuration<std::chrono::duration<double, std::milli>>() << '\n';
    std::cout << "As count(): " << timer.elapsed<std::chrono::duration<int, std::milli>>() << '\n';
}