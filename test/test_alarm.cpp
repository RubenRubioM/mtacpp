#include "../include/mta.h"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_all.hpp"
#include "catch2/catch_approx.hpp"
#include <thread>

using namespace std::chrono_literals;

using Catch::Matchers::Equals;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

constexpr int MAGIC_INT = 42;
constexpr float MAGIC_FLOAT = 42.42f;
constexpr bool MAGIC_BOOL = true;

class Foo
{
public:
    Foo() = default;
    // Foo::void(void) const
    void test_void_void(void) const {}
    // Foo::T(R&)
    int test_T_refR(int &x) const { return x_ + x; };

private:
    int x_{10};
};

// void(void) function
void test_void_void(void) {}
// void(T) function
void test_void_T([[maybe_unused]] int t) {}
// void(T, R, C) function
void test_void_T_R_C([[maybe_unused]] int t, [[maybe_unused]] float r, [[maybe_unused]] bool c) {}
// void(const T, const R, C)
void test_void_constT_constR_C([[maybe_unused]] const int t, [[maybe_unused]] const float r, [[maybe_unused]] bool c) {}
// void(const T, const& R, C)
void test_void_constT_constRefR_C([[maybe_unused]] const int t, [[maybe_unused]] const float &r, [[maybe_unused]] bool c) {}
// void(const T, R&&, C) TODO: Will it be possible to support rvalue references?
void test_void_constY_constRefRefR_C([[maybe_unused]] const int t, [[maybe_unused]] const float &&r, [[maybe_unused]] bool c) {}
// void(Foo)
void test_void_Foo([[maybe_unused]] Foo f) {}
// void(const Foo&)
void test_void_constRefFoo([[maybe_unused]] const Foo &f) {}
// T(void) function
[[nodiscard]] int test_int_void(void) { return MAGIC_INT; }

// TODO: Test function when return when execution is done.
TEST_CASE("Instantiates with constructor different versions of mta::Alarm for non-member functions", "[mta::Alarm]")
{
    constexpr const std::chrono::duration intervalTime{mta::DecimalMilliseconds(100)};
    Foo f{};
    SECTION("void(void) function")
    {
        mta::Alarm<void(void)> alarm{intervalTime, &test_void_void};
    }
    SECTION("void(T) function")
    {
        mta::Alarm<void(int)> alarm{intervalTime, &test_void_T, MAGIC_INT};
    }
    SECTION("void(T, R, C) function")
    {
        mta::Alarm<void(int, float, bool)> alarm{intervalTime, &test_void_T_R_C, MAGIC_INT, MAGIC_FLOAT, MAGIC_BOOL};
    }
    SECTION("void(const T, const R, C) function")
    {
        mta::Alarm<void(const int, const float, bool)> alarm{intervalTime, &test_void_constT_constR_C, MAGIC_INT, MAGIC_FLOAT, MAGIC_BOOL};
    }
    SECTION("void(T&, const R&, C) function")
    {
        int t = 10;
        const float r = 42.42f;
        mta::Alarm<void(const int, const float &, bool)> alarm{intervalTime, &test_void_constT_constRefR_C, t, r, MAGIC_BOOL};
    }
    SECTION("void(Foo) function")
    {
        mta::Alarm<void(Foo)> alarm{intervalTime, &test_void_Foo, Foo()};
    }
    SECTION("void(const Foo&) function")
    {
        mta::Alarm<void(const Foo &)> alarm{intervalTime, &test_void_constRefFoo, f};
    }
    SECTION("[[nodiscard]] T(void) function")
    {
        mta::Alarm<int(void)> alarm{intervalTime, &test_int_void};
    }
    SECTION("Foo::void(void) const function")
    {
        mta::Alarm<void(void)> alarm{};
        alarm.setMemberFunction(&Foo::test_void_void, f);
    }
    SECTION("Foo::T(R&) const function")
    {
        mta::Alarm<int(int&)> alarm{};
        alarm.setMemberFunction(&Foo::test_T_refR, f, MAGIC_INT);
    }
}