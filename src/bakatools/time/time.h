#pragma once

#include <bakatoolspch.h>

namespace Bk::Tools {
    using Nanosecond = std::ratio<1,1000000000>;
    using Microsecond = std::ratio<1,1000000>;
    using Millisecond = std::ratio<1,1000>;
    using Second = std::ratio<1,1>;
    using Minute = std::ratio<60, 1>;
    using Hour = std::ratio<3600, 1>;
    using Day = std::ratio<84600, 1>;

    using SysClock = std::chrono::system_clock;
    using SteadyClock = std::chrono::steady_clock;

    template<typename P>
    struct TimeSpan 
    {
        TimeSpan(int interval = 0) 
        : interval(std::chrono::duration<long int, P>(interval)) {}
        TimeSpan(std::chrono::duration<long int, P> interval)
        : interval(interval) {}

        template<typename T>
        TimeSpan<T> get_as()
        {
            return TimeSpan<T>(std::chrono::duration_cast<std::chrono::duration<long int, T>>(interval));
        }

        int count() { return interval.count(); }

        TimeSpan<P> operator-(TimeSpan<P>& time_span)
        {
            return TimeSpan<P>(interval - time_span.interval);
        }

        std::chrono::duration<long int, P> interval;
    };

    template<typename C, typename P>
    struct TimePoint
    {
        TimePoint() = default;
        TimePoint(std::chrono::time_point<C> point)
        {
            this->point = std::chrono::time_point_cast<std::chrono::duration<long int, P>>(point);
        }

        template<typename T>
        TimePoint<C, T> get_as()
        {
            return TimePoint<C, T>(std::chrono::time_point_cast<std::chrono::duration<long int, T>>(point));
        }

        TimeSpan<P> elasped()
        {
            return TimeSpan<P>(point.time_since_epoch());
        }

        bool is_steady()
        {
            return C::is_steady;
        }

        TimeSpan<P> operator-(TimePoint<C, P>& tp)
        {
            return TimeSpan<P>(point - tp.point);
        }

        static TimePoint<C, P> now() 
        {
            return TimePoint<C, P>(C::now());
        }

        std::chrono::time_point<C, std::chrono::duration<long int, P>> point;
    };
}