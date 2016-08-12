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

#define DEBUG 1

inline void polaris_printAbort(const char* str, ...) {
	va_list   pArgList;
	va_start(pArgList, str);
	vfprintf(stderr, str, pArgList);
	fprintf(stderr, "\n");
	va_end(pArgList);
	abort();
}

#define polaris_printLog(io, str, ...) \
		fprintf(io, str, ## __VA_ARGS__);fprintf(io, "\n");

#ifndef LOGD
#ifdef DEBUG
#define LOGD(str, ...) \
		polaris_printLog(stdout, str, ## __VA_ARGS__);
#else
#define LOGD(...) \
	;
#endif
#endif

#ifndef LOGE
#define LOGE(str, ...) \
		polaris_printLog(stderr, str, ## __VA_ARGS__);
#endif

#ifndef LOGW
#define LOGW(str, ...) \
		polaris_printLog(stderr, str, ## __VA_ARGS__);
#endif

#ifndef LOGI
#define LOGI(str, ...) \
		polaris_printLog(stdout, str, ## __VA_ARGS__);
#endif

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, str, ...)  \
	(cond) \
    ? ((void)polaris_printAbort(str, ##__VA_ARGS__)) \
    : (void)0
#endif

#ifndef LOG_ALWAYS_FATAL
#define LOG_ALWAYS_FATAL(str, ...)  \
		((void)polaris_printAbort(str, ##__VA_ARGS__))
#endif

#ifndef LOG_IF
#define LOG_IF(cond, str, ...)  \
	(cond) \
	? ((void)fprintf(stdout, str, ##__VA_ARGS__)) \
	: (void)0
#endif

#endif /* POLA_LOG_H_ */
