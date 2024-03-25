#pragma once

#include <bakatoolspch.h>
#include "time_span.h"

namespace Bk {
    template<typename C, typename P>
    struct TimePoint
    {
        TimePoint() = default;
        TimePoint(std::chrono::time_point<C> point)
        {
            this->point = std::chrono::time_point_cast<std::chrono::duration<long int, P>>(point);
        }

        template<typename Pi>
        TimePoint<C, Pi> as_unit()
        {
            return TimePoint<C, Pi>(std::chrono::time_point_cast<std::chrono::duration<long int, Pi>>(point));
        }

        template<typename Ci>
        TimePoint<Ci, P> as_clock()
        {
            return TimePoint(std::chrono::clock_cast<Ci>(point));
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