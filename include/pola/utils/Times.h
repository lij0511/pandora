/*
 * Times.h
 *
 *  Created on: 2015年11月30日
 *      Author: lijing
 */

#ifndef POLA_TIMES_H_
#define POLA_TIMES_H_

#include <stdint.h>
#include <time.h>

typedef int64_t p_nsecs_t;       // nano-seconds

namespace pola {

static p_nsecs_t systemTime(int clock) {
	static const clockid_t clocks[] = {
		CLOCK_REALTIME,
		CLOCK_MONOTONIC,
		CLOCK_PROCESS_CPUTIME_ID,
		CLOCK_THREAD_CPUTIME_ID
	};
	struct timespec t;
	t.tv_sec = t.tv_nsec = 0;
	clock_gettime(clocks[clock], &t);
	return p_nsecs_t(t.tv_sec)*1000000000LL + t.tv_nsec;
}

static inline p_nsecs_t seconds_to_nanoseconds(p_nsecs_t secs)
{
    return secs*1000000000;
}

static inline p_nsecs_t milliseconds_to_nanoseconds(p_nsecs_t secs)
{
    return secs*1000000;
}

static inline p_nsecs_t microseconds_to_nanoseconds(p_nsecs_t secs)
{
    return secs*1000;
}

static inline p_nsecs_t nanoseconds_to_seconds(p_nsecs_t secs)
{
    return secs/1000000000;
}

static inline p_nsecs_t nanoseconds_to_milliseconds(p_nsecs_t secs)
{
    return secs/1000000;
}

static inline p_nsecs_t nanoseconds_to_microseconds(p_nsecs_t secs)
{
    return secs/1000;
}

static inline p_nsecs_t s2ns(p_nsecs_t v)  {return seconds_to_nanoseconds(v);}
static inline p_nsecs_t ms2ns(p_nsecs_t v) {return milliseconds_to_nanoseconds(v);}
static inline p_nsecs_t us2ns(p_nsecs_t v) {return microseconds_to_nanoseconds(v);}
static inline p_nsecs_t ns2s(p_nsecs_t v)  {return nanoseconds_to_seconds(v);}
static inline p_nsecs_t ns2ms(p_nsecs_t v) {return nanoseconds_to_milliseconds(v);}
static inline p_nsecs_t ns2us(p_nsecs_t v) {return nanoseconds_to_microseconds(v);}

static inline p_nsecs_t seconds(p_nsecs_t v)      { return s2ns(v); }
static inline p_nsecs_t milliseconds(p_nsecs_t v) { return ms2ns(v); }
static inline p_nsecs_t microseconds(p_nsecs_t v) { return us2ns(v); }

static p_nsecs_t uptimeMillis() {
	return nanoseconds_to_milliseconds(systemTime(1));
}

}
#endif /* POLA_TIMES_H_ */
