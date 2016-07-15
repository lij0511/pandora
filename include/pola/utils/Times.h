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

typedef int64_t nsecs_t;       // nano-seconds

static nsecs_t systemTime(int clock) {
	static const clockid_t clocks[] = {
		CLOCK_REALTIME,
		CLOCK_MONOTONIC,
		CLOCK_PROCESS_CPUTIME_ID,
		CLOCK_THREAD_CPUTIME_ID
	};
	struct timespec t;
	t.tv_sec = t.tv_nsec = 0;
	clock_gettime(clocks[clock], &t);
	return nsecs_t(t.tv_sec)*1000000000LL + t.tv_nsec;
}

static inline nsecs_t seconds_to_nanoseconds(nsecs_t secs)
{
    return secs*1000000000;
}

static inline nsecs_t milliseconds_to_nanoseconds(nsecs_t secs)
{
    return secs*1000000;
}

static inline nsecs_t microseconds_to_nanoseconds(nsecs_t secs)
{
    return secs*1000;
}

static inline nsecs_t nanoseconds_to_seconds(nsecs_t secs)
{
    return secs/1000000000;
}

static inline nsecs_t nanoseconds_to_milliseconds(nsecs_t secs)
{
    return secs/1000000;
}

static inline nsecs_t nanoseconds_to_microseconds(nsecs_t secs)
{
    return secs/1000;
}

static inline nsecs_t s2ns(nsecs_t v)  {return seconds_to_nanoseconds(v);}
static inline nsecs_t ms2ns(nsecs_t v) {return milliseconds_to_nanoseconds(v);}
static inline nsecs_t us2ns(nsecs_t v) {return microseconds_to_nanoseconds(v);}
static inline nsecs_t ns2s(nsecs_t v)  {return nanoseconds_to_seconds(v);}
static inline nsecs_t ns2ms(nsecs_t v) {return nanoseconds_to_milliseconds(v);}
static inline nsecs_t ns2us(nsecs_t v) {return nanoseconds_to_microseconds(v);}

static inline nsecs_t seconds(nsecs_t v)      { return s2ns(v); }
static inline nsecs_t milliseconds(nsecs_t v) { return ms2ns(v); }
static inline nsecs_t microseconds(nsecs_t v) { return us2ns(v); }

static nsecs_t uptimeMillis() {
	return nanoseconds_to_milliseconds(systemTime(1));
}
#endif /* POLA_TIMES_H_ */
