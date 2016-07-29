/*
 * Log.h
 *
 *  Created on: 2015年12月4日
 *      Author: lijing
 */

#ifndef POLA_LOG_H_
#define POLA_LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//#define DEBUG 1

inline void polaris_printAssert(bool cond, const char* str, ...) {
	if (cond) {
		va_list   pArgList;
		va_start(pArgList, str);
		fprintf(stdout, str, pArgList);
		va_end(pArgList);
		abort();
	}
}

#ifndef LOGD
#ifdef DEBUG
#define LOGD(str, ...) \
		(void)fprintf(stdout, str, ## __VA_ARGS__);
#else
#define LOGD(...) \
	;
#endif
#endif

#ifndef LOGE
#define LOGE(str, ...) \
	(void)fprintf(stderr, str, ## __VA_ARGS__);
#endif

#ifndef LOGW
#define LOGW(str, ...) \
	(void)fprintf(stderr, str, ## __VA_ARGS__);
#endif

#ifndef LOGI
#define LOGI(str, ...) \
	fprintf(stdout, str, ## __VA_ARGS__);
#endif

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, str, ...)  \
	(cond) \
    ? ((void)polaris_printAssert(#cond, str, ##__VA_ARGS__)) \
    : (void)0
#endif

#ifndef LOG_ALWAYS_FATAL
#define LOG_ALWAYS_FATAL(str, ...)  \
    ((void)polaris_printAssert(true, str, ##__VA_ARGS__))
#endif

#ifndef LOG_IF
#define LOG_IF(cond, str, ...)  \
	(cond) \
	? ((void)fprintf(stdout, str, ##__VA_ARGS__)) \
	: (void)0
#endif

#endif /* POLA_LOG_H_ */
