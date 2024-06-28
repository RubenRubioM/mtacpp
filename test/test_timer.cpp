#include "../include/mta.h"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_all.hpp"
#include "catch2/catch_approx.hpp"
#include <thread>

using namespace std::chrono_literals;

using Catch::Matchers::Equals;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

constexpr double TIMER_ERROR_THRESHOLD = 0.01;

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
        constexpr double expectedValue = 100'000'000;
        const auto timeCountDecimal = timer.elapsed();
        CHECK_THAT(timeCountDecimal, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        const auto timeCountInteger = timer.elapsed<mta::IntegerNanoseconds>();
        CHECK_THAT(timeCountInteger, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK_NOTHROW(timer.elapsedAsDuration());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerNanoseconds>());
    }
    SECTION("Convert to microseconds")
    {
        constexpr double expectedValue = 100'000;
        const auto timeCountDecimal = timer.elapsed<mta::DecimalMicroseconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerMicroseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK_THAT(timeCountInteger, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalMicroseconds>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerMicroseconds>());
    }
    SECTION("Convert to milliseconds")
    {
        constexpr double expectedValue = 100;
        const auto timeCountDecimal = timer.elapsed<mta::DecimalMilliseconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerMilliseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK_THAT(timeCountInteger, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalMilliseconds>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerMilliseconds>());
    }
    SECTION("Convert to centiseconds")
    {
        constexpr double expectedValue = 10;
        const auto timeCountDecimal = timer.elapsed<mta::DecimalCentiseconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerCentiseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK_THAT(timeCountInteger, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalCentiseconds>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerCentiseconds>());
    }
    SECTION("Convert to deciseconds")
    {
        constexpr double expectedValue = 1;
        const auto timeCountDecimal = timer.elapsed<mta::DecimalDeciseconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerDeciseconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK(timeCountInteger == expectedValue);
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalDeciseconds>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerDeciseconds>());
    }
    SECTION("Convert to seconds")
    {
        constexpr double expectedValue = 0.1;
        const auto timeCountDecimal = timer.elapsed<mta::DecimalSeconds>();
        const auto timeCountInteger = timer.elapsed<mta::IntegerSeconds>();
        CHECK_THAT(timeCountDecimal, WithinRel(expectedValue, TIMER_ERROR_THRESHOLD));
        CHECK(timeCountInteger == 0);
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalSeconds>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerSeconds>());
    }

    // With units above seconds, the decimal point failure raises too much for a short sleep time of 100ms.
    // In order to not delay too much the testing we are avoiding testing the other units.
    
    SECTION("Convert to minutes")
    {
        CHECK_NOTHROW(timer.elapsed<mta::DecimalMinutes>());
        CHECK_NOTHROW(timer.elapsed<mta::IntegerMinutes>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalMinutes>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerMinutes>());
    }
    SECTION("Convert to hours")
    {
        CHECK_NOTHROW(timer.elapsed<mta::DecimalHours>());
        CHECK_NOTHROW(timer.elapsed<mta::IntegerHours>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalHours>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerHours>());
    }
    SECTION("Convert to days")
    {
        CHECK_NOTHROW(timer.elapsed<mta::DecimalDays>());
        CHECK_NOTHROW(timer.elapsed<mta::IntegerDays>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalDays>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerDays>());
    }
    SECTION("Convert to weeks")
    {
        CHECK_NOTHROW(timer.elapsed<mta::DecimalWeeks>());
        CHECK_NOTHROW(timer.elapsed<mta::IntegerWeeks>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalWeeks>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerWeeks>());
    }
    SECTION("Convert to months")
    {
        CHECK_NOTHROW(timer.elapsed<mta::DecimalMonths>());
        CHECK_NOTHROW(timer.elapsed<mta::IntegerMonths>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalMonths>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerMonths>());
    }
    SECTION("Convert to years")
    {
        CHECK_NOTHROW(timer.elapsed<mta::DecimalYears>());
        CHECK_NOTHROW(timer.elapsed<mta::IntegerYears>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::DecimalYears>());
        CHECK_NOTHROW(timer.elapsedAsDuration<mta::IntegerYears>());
    }
}

TEST_CASE("mta::Timer::stop is called without calling start. Then time should be 0", "[mta::Timer]")
{
    mta::Timer timer{};
    timer.stop();
    REQUIRE(timer.isStopped());
    REQUIRE(timer.elapsed() == 0);
}