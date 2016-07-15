/*
 * Typeface.h
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#ifndef POLA_TYPEFACE_H_
#define POLA_TYPEFACE_H_

#include "pola/utils/RefBase.h"

namespace pola {
namespace graphic {

class Typeface: public utils::RefBase<Typeface> {
public:
	Typeface();
	virtual ~Typeface();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_TYPEFACE_H_ */
