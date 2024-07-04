#include "mta.h"

#include <chrono>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

class Foo
{
public:
    Foo() = default;
    ~Foo() = default;

    auto test(int x, double y) -> bool
    {
        std::cout << "Foo::test: " << x << " " << y << "\n";
        return true;
    }
};

[[nodiscard]] auto test(int x) -> bool
{
    std::cout << "test: " << x << '\n';
    return false;
}

auto main() -> int
{
    std::cout << "Executing mta in thread " << std::this_thread::get_id() << '\n';
    // Call with function
    mta::Alarm<bool(int)> alarm{};
    alarm.setInterval(std::chrono::milliseconds(3000));
    alarm.setFunction(&test, 10);
    alarm.exec(0);
    // Call with member function
    Foo f{};
    mta::Alarm<bool(int, double)> alarm2{};
    alarm2.setInterval(std::chrono::milliseconds(3000));
    alarm2.setMemberFunction(&Foo::test, f, 20, 50.0f);
    alarm2.exec(0, 0);
    std::cout << "Main\n";
}