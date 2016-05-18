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

//#define DEBUG 1

#ifdef DEBUG
#define LOGD(...) \
	fprintf(stdout, __VA_ARGS__);
#else
#define LOGD(...) \
	;
#endif

#define LOGE(...) \
	fprintf(stderr, __VA_ARGS__);

#define LOGI(...) \
	fprintf(stdout, __VA_ARGS__);

#endif /* LOG_H_ */
