/*
 * Math.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#include <math.h>

#ifndef POLA_MATH_H_
#define POLA_MATH_H_

namespace pola {
namespace utils {

template<typename TYPE>
inline const TYPE fclamp(const TYPE& value, const TYPE& low, const TYPE& high) {
	return fmin(fmax(value, low), high);
}

}
}

#endif /* POLA_MATH_H_ */
