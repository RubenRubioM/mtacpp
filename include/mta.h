#ifndef MTA_H
#define MTA_H

#include <iostream>
#include <chrono>

namespace mta
{
    static constexpr uint64_t secondsRatio = 1;
    static constexpr uint64_t minutesRatio = secondsRatio * 60;
    static constexpr uint64_t hoursRatio = minutesRatio * 60;
    static constexpr uint64_t daysRatio = hoursRatio * 24;
    static constexpr uint64_t weeksRatio = daysRatio * 7;
    static constexpr uint64_t monthsRatio = 2629746;
    static constexpr uint64_t yearsRatio = 31556952;

    using DecimalNanoseconds = std::chrono::duration<double, std::nano>;
    using DecimalMicroseconds = std::chrono::duration<double, std::micro>;
    using DecimalMilliseconds = std::chrono::duration<double, std::milli>;
    using DecimalCentiseconds = std::chrono::duration<double, std::centi>;
    using DecimalDeciseconds = std::chrono::duration<double, std::deci>;
    using DecimalSeconds = std::chrono::duration<double, std::ratio<secondsRatio>>;
    using DecimalMinutes = std::chrono::duration<double, std::ratio<minutesRatio>>;
    using DecimalHours = std::chrono::duration<double, std::ratio<hoursRatio>>;
    using DecimalDays = std::chrono::duration<double, std::ratio<daysRatio>>;
    using DecimalWeeks = std::chrono::duration<double, std::ratio<weeksRatio>>;
    using DecimalMonths = std::chrono::duration<double, std::ratio<monthsRatio>>;
    using DecimalYears = std::chrono::duration<double, std::ratio<yearsRatio>>;

    using IntegerNanoseconds = std::chrono::duration<uint64_t, std::nano>;
    using IntegerMicroseconds = std::chrono::duration<uint64_t, std::micro>;
    using IntegerMilliseconds = std::chrono::duration<uint64_t, std::milli>;
    using IntegerCentiseconds = std::chrono::duration<uint64_t, std::centi>;
    using IntegerDeciseconds = std::chrono::duration<uint64_t, std::deci>;
    using IntegerSeconds = std::chrono::duration<uint64_t, std::ratio<secondsRatio>>;
    using IntegerMinutes = std::chrono::duration<uint64_t, std::ratio<minutesRatio>>;
    using IntegerHours = std::chrono::duration<uint64_t, std::ratio<hoursRatio>>;
    using IntegerDays = std::chrono::duration<uint64_t, std::ratio<daysRatio>>;
    using IntegerWeeks = std::chrono::duration<uint64_t, std::ratio<weeksRatio>>;
    using IntegerMonths = std::chrono::duration<uint64_t, std::ratio<monthsRatio>>;
    using IntegerYears = std::chrono::duration<uint64_t, std::ratio<yearsRatio>>;

    template <typename Clock = std::chrono::high_resolution_clock>
    class Timer
    {
    public:

        constexpr explicit Timer() noexcept = default;
        ~Timer() noexcept = default;

        void start() noexcept
        {
            init = Clock::now();
        }

        /// @brief Returns the elapsed time since Timer::start was called
        /// @tparam ConvertibleDuration std::chrono::duration to convert to this unit.
        /// @note Encourage to use the `using` defined in the namespace `mta` that starts from Decimal and Integer. 
        ///       You can also provide your own conversion directly from chrono, e.g: std::chrono::milliseconds.
        ///       The default value is `mta::DecimalNanoseconds`, nanoseconds in floating point representation.
        /// @return The value of T between Timer::start and now in the underlying type used in ConvertibleDuration.
        template <typename ConvertibleDuration = DecimalNanoseconds>
        [[nodiscard]] ConvertibleDuration::rep elapsed() const noexcept
        {
            return elapsedAsDuration<ConvertibleDuration>().count();
        }

        /// @brief Returns the elapsed time since Timer::start was called as an std::chrono::duration
        /// @tparam ConvertibleDuration std::chrono::duration to convert to this unit.
        /// @note Encourage to use the `using` defined in the namespace `mta` that starts from Decimal and Integer. 
        ///       You can also provide your own conversion directly from chrono, e.g: std::chrono::milliseconds.
        ///       The default value is `mta::DecimalNanoseconds`, nanoseconds in floating point representation.
        /// @return The value of T between Timer::start and now.
        template <typename ConvertibleDuration = DecimalNanoseconds>
        [[nodiscard]] ConvertibleDuration elapsedAsDuration() const noexcept
        {
            return std::chrono::duration_cast<ConvertibleDuration>(Clock::now() - init);
        }

    private:
        std::chrono::time_point<Clock> init{}; /// Initial time_point. Setted in Timer::start.
    }; // class Timer

} // namespace mta

#endif
