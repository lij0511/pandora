/*
 * Reader.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef POLA_READER_H_
#define POLA_READER_H_

#include "io/InputStream.h"

namespace pola {
namespace io {

class Reader: public InputStream {
public:
	virtual ~Reader() {};
};

} /* namespace io */
} /* namespace pola */

#endif /* POLA_READER_H_ */
