/*
 * OutputStream.cpp
 *
 *  Created on: 2016年8月26日
 *      Author: lijing
 */

#include "pola/io/OutputStream.h"

namespace pola {
namespace io {

OutputStream::OutputStream() : mClosed(false) {
}

OutputStream::~OutputStream() {
}

void OutputStream::flush() {
}

} /* namespace io */
} /* namespace pola */
