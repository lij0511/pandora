/*
 * IOUtils.h
 *
 *  Created on: 2016年5月26日
 *      Author: lijing
 */

#ifndef POLA_IOUTILS_H_
#define POLA_IOUTILS_H_

#include "pola/io/InputStream.h"

#include <vector>

namespace pola {
namespace io {

template<typename TYPE>
std::vector<TYPE> copyStreamToVector(InputStream* is) {
	std::vector<TYPE> vector;
	size_t length = is->getLength();
	size_t position = is->getPosition();
	if (length > 0 && position < length) {
		length = length - position;
		vector.resize(length / sizeof(TYPE));
		size_t len = is->read(vector.editArray(), length);
		if (len < length) {
			vector.resize(len / sizeof(TYPE));
		}
	} else {
		size_t size = sizeof(TYPE);
		void* ch = new char[size];
		while (is->read(ch, size) == size) {
			vector.push_back(*((TYPE*) ch));
		}
	}
	return vector;
}

}
}

#endif /* POLA_IOUTILS_H_ */
