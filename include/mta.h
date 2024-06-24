#ifndef MTA_H
#define MTA_H

#include <iostream>
#include <chrono>

namespace mta
{
    template <typename Duration = std::chrono::duration<double, std::nano>,
              typename Clock = std::chrono::system_clock>
    class Timer
    {
    public:
        explicit Timer() noexcept = default;
        ~Timer() noexcept = default;

        void start() noexcept
        {
            init = Clock::now();
        }

        template <typename ConvertibleDuration = Duration>
        [[nodiscard]] ConvertibleDuration::rep elapsed() const noexcept
        {
            return elapsedAsDuration<ConvertibleDuration>().count();
        }

        template <typename ConvertibleDuration = Duration>
        [[nodiscard]] ConvertibleDuration elapsedAsDuration() const noexcept
        {
            return std::chrono::duration_cast<ConvertibleDuration>(Clock::now() - init);
        }

        // TODO: It is a good thing to delete the copy constructor and copy assignment?
        Timer(const Timer &) = delete;
        Timer operator=(const Timer &) = delete;

    private:
        std::chrono::time_point<Clock> init{};
    }; // class Timer

} // namespace mta

#endif