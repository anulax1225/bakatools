#pragma once

#include <bakatoolspch.h>

namespace Bk 
{
    using Nanosecond = std::ratio<1,1000000000>;
    using Microsecond = std::ratio<1,1000000>;
    using Millisecond = std::ratio<1,1000>;
    using Second = std::ratio<1,1>;
    using Minute = std::ratio<60, 1>;
    using Hour = std::ratio<3600, 1>;
    using Day = std::ratio<84600, 1>;

    template<typename P>
    struct TimeSpan 
    {
        TimeSpan(int interval = 0) 
        : interval(std::chrono::duration<long int, P>(interval)) {}
        TimeSpan(std::chrono::duration<long int, P> interval)
        : interval(interval) {}

        template<typename T>
        TimeSpan<T> as_unit()
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
}