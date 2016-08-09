/*
 * Math.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#include <cmath>
#include <stdlib.h>
#include <time.h>

#ifndef POLA_MATH_H_
#define POLA_MATH_H_

namespace pola {
namespace utils {


inline double random(double start = 0, double end = 1) {
	static bool sand = false;
	if (!sand) {
		srand((unsigned)time(0));
		sand = true;
	}
	return start + (end - start) * double(rand()) / (RAND_MAX);
}

template<typename TYPE>
inline const TYPE fclamp(const TYPE& value, const TYPE& low, const TYPE& high) {
	return fmin(fmax(value, low), high);
}

}
}

#endif /* POLA_MATH_H_ */
