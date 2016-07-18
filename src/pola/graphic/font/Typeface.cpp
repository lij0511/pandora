/*
 * Typeface.cpp
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#include "pola/graphic/font/Typeface.h"

namespace pola {
namespace graphic {

Typeface::~Typeface() {
}

Typeface::Style Typeface::style() const {
	return mStyle;
}

} /* namespace graphic */
} /* namespace pola */
