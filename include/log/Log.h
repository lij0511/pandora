/*
 * Log.h
 *
 *  Created on: 2015年12月4日
 *      Author: lijing
 */

#ifndef LOG_H_
#define LOG_H_

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

#ifndef LOGE
#ifdef DEBUG
#define LOGD(str, ...) \
	fprintf(stdout, str, __VA_ARGS__);
#else
#define LOGD(...) \
	;
#endif
#endif

#ifndef LOGE
#define LOGE(str, ...) \
	fprintf(stderr, str, __VA_ARGS__);
#endif

#ifndef LOGI
#define LOGI(str, ...) \
	fprintf(stdout, str, __VA_ARGS__);
#endif

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, str, ...)  \
	(cond) \
    ? ((void)polaris_printAssert(#cond, str, ##__VA_ARGS__)) \
    : (void)0
#endif

#ifndef LOG_IF
#define LOG_IF(cond, str, ...)  \
    if (cond) \
    {fprintf(stdout, str, __VA_ARGS__); abort();}
#endif

#endif /* LOG_H_ */
