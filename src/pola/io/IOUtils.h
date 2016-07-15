/*
 * IOUtils.h
 *
 *  Created on: 2016年5月26日
 *      Author: lijing
 */

#ifndef POLA_IOUTILS_H_
#define POLA_IOUTILS_H_

#include "pola/utils/Vector.h"
#include "pola/io/InputStream.h"

namespace pola {
namespace io {

template<typename TYPE>
utils::Vector<TYPE> copyStreamToVector(InputStream* is) {
	utils::Vector<TYPE> vector;
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
			vector.push(*((TYPE*) ch));
		}
	}
	return vector;
}

}
}

#endif /* POLA_IOUTILS_H_ */
