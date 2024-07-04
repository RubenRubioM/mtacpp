#ifndef MTA_H
#define MTA_H

#include <iostream>
#include <chrono>
#include <functional>
#include <utility>

namespace mta
{
    using decimalType = double;
    using integerType = int64_t;

    static constexpr integerType secondsRatio = 1LL;
    /// How many seconds are in a minute.
    static constexpr integerType minutesRatio = secondsRatio * 60LL;
    /// How many seconds are in an hour.
    static constexpr integerType hoursRatio = minutesRatio * 60LL;
    /// How many seconds are in a day.
    static constexpr integerType daysRatio = hoursRatio * 24LL;
    /// How many seconds are in a week.
    static constexpr integerType weeksRatio = daysRatio * 7LL;
    /// How many seconds are in a month.
    static constexpr integerType monthsRatio = 2629746LL;
    /// How many seconds are in a year.
    static constexpr integerType yearsRatio = 31556952LL;

    /// Floating point representation for `std::chrono::duration` in nanoseconds.
    using DecimalNanoseconds = std::chrono::duration<decimalType, std::nano>;
    /// Floating point representation for `std::chrono::duration` in microseconds.
    using DecimalMicroseconds = std::chrono::duration<decimalType, std::micro>;
    /// Floating point representation for `std::chrono::duration` in milliseconds.
    using DecimalMilliseconds = std::chrono::duration<decimalType, std::milli>;
    /// Floating point representation for `std::chrono::duration` in centiseconds.
    using DecimalCentiseconds = std::chrono::duration<decimalType, std::centi>;
    /// Floating point representation for `std::chrono::duration` in deciseconds.
    using DecimalDeciseconds = std::chrono::duration<decimalType, std::deci>;
    /// Floating point representation for `std::chrono::duration` in seconds.
    using DecimalSeconds = std::chrono::duration<decimalType, std::ratio<secondsRatio>>;
    /// Floating point representation for `std::chrono::duration` in minutes.
    using DecimalMinutes = std::chrono::duration<decimalType, std::ratio<minutesRatio>>;
    /// Floating point representation for `std::chrono::duration` in hours.
    using DecimalHours = std::chrono::duration<decimalType, std::ratio<hoursRatio>>;
    /// Floating point representation for `std::chrono::duration` in days.
    using DecimalDays = std::chrono::duration<decimalType, std::ratio<daysRatio>>;
    /// Floating point representation for `std::chrono::duration` in weeks.
    using DecimalWeeks = std::chrono::duration<decimalType, std::ratio<weeksRatio>>;
    /// Floating point representation for `std::chrono::duration` in months.
    using DecimalMonths = std::chrono::duration<decimalType, std::ratio<monthsRatio>>;
    /// Floating point representation for `std::chrono::duration` in years.
    using DecimalYears = std::chrono::duration<decimalType, std::ratio<yearsRatio>>;

    /// Integer representation for `std::chrono::duration` in nanoseconds.
    using IntegerNanoseconds = std::chrono::duration<integerType, std::nano>;
    /// Integer representation for `std::chrono::duration` in microseconds.
    using IntegerMicroseconds = std::chrono::duration<integerType, std::micro>;
    /// Integer representation for `std::chrono::duration` in milliseconds.
    using IntegerMilliseconds = std::chrono::duration<integerType, std::milli>;
    /// Integer representation for `std::chrono::duration` in centiseconds.
    using IntegerCentiseconds = std::chrono::duration<integerType, std::centi>;
    /// Integer representation for `std::chrono::duration` in deciseconds.
    using IntegerDeciseconds = std::chrono::duration<integerType, std::deci>;
    /// Integer representation for `std::chrono::duration` in seconds.
    using IntegerSeconds = std::chrono::duration<integerType, std::ratio<secondsRatio>>;
    /// Integer representation for `std::chrono::duration` in minutes.
    using IntegerMinutes = std::chrono::duration<integerType, std::ratio<minutesRatio>>;
    /// Integer representation for `std::chrono::duration` in hours.
    using IntegerHours = std::chrono::duration<integerType, std::ratio<hoursRatio>>;
    /// Integer representation for `std::chrono::duration` in days.
    using IntegerDays = std::chrono::duration<integerType, std::ratio<daysRatio>>;
    /// Integer representation for `std::chrono::duration` in weeks.
    using IntegerWeeks = std::chrono::duration<integerType, std::ratio<weeksRatio>>;
    /// Integer representation for `std::chrono::duration` in months.
    using IntegerMonths = std::chrono::duration<integerType, std::ratio<monthsRatio>>;
    /// Integer representation for `std::chrono::duration` in years.
    using IntegerYears = std::chrono::duration<integerType, std::ratio<yearsRatio>>;

    /// @brief Timer class used to calculate the time elapsed since the start of itself.
    /// @tparam Clock - The type of clock used to calculate the time. Default value is `std::chrono::high_resolution_clock`.
    template <typename Clock = std::chrono::high_resolution_clock>
    class Timer
    {
    public:
        /// @brief Default constructor.
        constexpr explicit Timer() noexcept = default;

        /// @brief Destructor
        ~Timer() noexcept = default;

        /// @brief Starts the timer. Sets `Timer::init_` to `Clock::now()`
        void start() noexcept
        {
            init_ = Clock::now();
        }

        /// @brief Stops the timer. Sets Timer::finish_ to Clock::now()
        /// @note If `Timer::stop` is called without calling `Timer::start` first, the time will be 0.
        void stop() noexcept
        {
            finish_ = Clock::now();
            if (init_ == std::chrono::time_point<Clock>()) [[unlikely]]
                init_ = finish_;
        }

        /// @brief If the timer has been stopped
        /// @return `true` if `Timer::stop` has been called before.
        /// @return `false` otherwise.
        [[nodiscard]] constexpr bool isStopped() const
        {
            return finish_ != std::chrono::time_point<Clock>();
        }

        /// @brief Returns the elapsed time since `Timer::start` was called
        /// @tparam ConvertibleDuration `std::chrono::duration` to convert to this unit.
        /// @note Encourage to use the `using` defined in the namespace `mta` that starts from Decimal and Integer.
        ///       You can also provide your own conversion directly from chrono, e.g: `std::chrono::milliseconds`.
        ///       The default value is `mta::DecimalNanoseconds`, nanoseconds in floating point representation.
        /// @return The value of T between `Timer::start` and now in the underlying type used in `ConvertibleDuration`.
        template <typename ConvertibleDuration = DecimalNanoseconds>
        [[nodiscard]] ConvertibleDuration::rep elapsed() const noexcept
        {
            return elapsedAsDuration<ConvertibleDuration>().count();
        }

        /// @brief Returns the elapsed time since `Timer::start` was called as an `std::chrono::duration`
        /// @tparam ConvertibleDuration `std::chrono::duration` to convert to this unit.
        /// @note Encourage to use the `using` defined in the namespace `mta` that starts from Decimal and Integer.
        ///       You can also provide your own conversion directly from chrono, e.g: `std::chrono::milliseconds`.
        ///       The default value is `mta::DecimalNanoseconds`, nanoseconds in floating point representation.
        /// @return The value of T between `Timer::start` and now.
        template <typename ConvertibleDuration = DecimalNanoseconds>
        [[nodiscard]] ConvertibleDuration elapsedAsDuration() const noexcept
        {
            std::chrono::time_point finish = finish_ != std::chrono::time_point<Clock>() ? finish_ : Clock::now();
            return std::chrono::duration_cast<ConvertibleDuration>(finish - init_);
        }

    private:
        std::chrono::time_point<Clock> init_{};   /// Initial time_point. Setted in Timer::start.
        std::chrono::time_point<Clock> finish_{}; /// Finish time_point. Setted in Timer::stop.
    }; // class Timer

    /// @brief Alarm class used to trigger a function, member function or lambda function when a criteria is met.
    /// todo: add more information when the class is finished.
    template <typename Func,
              typename IntervalSleepType = DecimalMilliseconds>
    class Alarm
    {
    public:
        explicit Alarm() noexcept = default;
        ~Alarm() noexcept = default;

        /// @brief Sets the interval of time to execute the alarm.
        /// @param time The time of the interval in std::chrono::duration.
        void setInterval(const IntervalSleepType &time) noexcept
        {
            intervalTime_ = time;
        }

        /// @brief Sets the non-member function to be executed.
        /// @param f The function.
        /// @param ...args Arguments that `f` will be executed with.
        template <typename... Args>
        void setFunction(Func f, Args&&... args) noexcept
        {
            func_ = std::bind(f, std::forward<Args>(args)...);
        }

        /// @brief Sets the member function to be executed.
        /// @param f The member function.
        /// @param c The object reference to execute `f`.
        /// @param ...args Arguments that `f` will be executed with.
        template <typename... Args>
        void setMemberFunction(auto f, auto c, Args&&... args) noexcept
        {
            func_ = std::bind(f, c, std::forward<Args>(args)...);
        }

        template <typename... Args>
        auto exec(Args&&... args) const noexcept -> decltype(auto)
        {
            func_(std::forward<Args>(args)...);
        }

    private:
        IntervalSleepType intervalTime_{}; /// Time to execute the alarm.
        std::function<Func> func_{};       /// Function to be executed when `intervalTime_` is finished.
    }; // class Alarm
} // namespace mta

#endif
