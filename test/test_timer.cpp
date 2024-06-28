#include "../include/mta.h"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_all.hpp"
#include "catch2/catch_approx.hpp"
#include <thread>

using namespace std::chrono_literals;

using Catch::Matchers::Equals;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("Ratio variables are correct", "[mta::Timer]")
{
    REQUIRE(mta::secondsRatio == 1LL);
    REQUIRE(mta::minutesRatio == 60LL);
    REQUIRE(mta::hoursRatio == 3600LL);
    REQUIRE(mta::daysRatio == 86'400LL);
    REQUIRE(mta::weeksRatio == 604'800LL);
    REQUIRE(mta::monthsRatio == 2'629'746LL);
    REQUIRE(mta::yearsRatio == 31'556'952LL);
}

TEST_CASE("mta::Timer starts and stops without problems, testing Timer::isStopped()", "[mta::Timer]")
{
    mta::Timer timer{};
    timer.start();
    REQUIRE_FALSE(timer.isStopped());
    timer.stop();
    REQUIRE(timer.isStopped());
}

TEST_CASE("mta::Timer is instantiated with different clocks", "[mta::Timer]")
{
    [[maybe_unused]] mta::Timer<std::chrono::system_clock> systemClockTimer{};
    [[maybe_unused]] mta::Timer<std::chrono::steady_clock> steadyClockTimer{};
    [[maybe_unused]] mta::Timer<std::chrono::high_resolution_clock> highResolutionClockTimer{};
}

//TODO: Test elapsedAsDuration aswell
TEST_CASE("mta::Timer with elapsed and elapsedAsDuration with different units", "[mta::Timer]")
{
    constexpr uint64_t sleepTimeInMs = 100;
    mta::Timer<std::chrono::high_resolution_clock> timer{};
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeInMs));
    timer.stop();
    REQUIRE(timer.isStopped());

    SECTION("Convert to nanoseconds")
    {
        const auto timeCountDecimal = timer.elapsed();
        const auto timeCountInteger = timer.elapsed<mta::IntegerNanoseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(100'000'000, 0.01));
        CHECK_THAT(timeCountInteger, WithinRel(100'000'000, 0.01));
    }
    SECTION("Convert to microseconds")
    {
        const auto timeCountDecimal = timer.elapsed<mta::DecimalMicroseconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerMicroseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(100'000, 0.01));
        CHECK_THAT(timeCountInteger, WithinRel(100'000, 0.01));
    }
    SECTION("Convert to milliseconds")
    {
        const auto timeCountDecimal = timer.elapsed<mta::DecimalMilliseconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerMilliseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(100, 0.01));
        CHECK_THAT(timeCountInteger, WithinRel(100, 0.01));
    }
    SECTION("Convert to centiseconds")
    {
        const auto timeCountDecimal = timer.elapsed<mta::DecimalCentiseconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerCentiseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(10, 0.01));
        CHECK_THAT(timeCountInteger, WithinRel(10, 0.01));
    }
    SECTION("Convert to deciseconds")
    {
        const auto timeCountDecimal = timer.elapsed<mta::DecimalDeciseconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerDeciseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(1, 0.01));
        CHECK(timeCountInteger == 1);
    }
    SECTION("Convert to seconds")
    {
        const auto timeCountDecimal = timer.elapsed<mta::DecimalSeconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerSeconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(0.1, 0.01));
        CHECK(timeCountInteger == 0);
    }
    
    // With unit below seconds, the decimal point failure raises too much for a short sleep time of 100ms.
    // In order to not delay too much the testing we are avoiding testing the other units.
}

TEST_CASE("mta::Timer::stop is called without calling start. Then time should be 0", "[mta::Timer]")
{
    mta::Timer timer{};
    timer.stop();
    REQUIRE(timer.isStopped());
    REQUIRE(timer.elapsed() == 0);
}