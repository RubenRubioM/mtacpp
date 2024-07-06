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

    [[nodiscard]] auto test(int x, double y) const -> bool
    {
        std::cout << "Foo::test: " << x << " " << y << "\n";
        return true;
    }
};

[[nodiscard]] auto test(int x, bool y) -> bool
{
    std::cout << "test: " << x << " " <<  y << '\n';
    return false;
}

auto main() -> int
{
    std::cout << "Executing mta in thread " << std::this_thread::get_id() << '\n';
    // Call with function
    mta::Alarm<bool(int, bool)> alarm{mta::DecimalMilliseconds(3000), &test, 10, true};
    alarm.exec(0, false);
    // Call with member function
    Foo f{};
    mta::Alarm<bool(int, double)> alarm2{};
    alarm2.setInterval(std::chrono::milliseconds(3000));
    alarm2.setMemberFunction(&Foo::test, f, 20, 50.0f);
    alarm2.exec(0, 0);
    std::cout << "Main\n";
}