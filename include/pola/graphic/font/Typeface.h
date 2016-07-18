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
	enum Style {
		kNormal = 0,
		kBold   = 0x01,
		kItalic = 0x02,
		kBoldItalic = 0x03
	};

	virtual ~Typeface();

	Style style() const;

	/** Returns true if getStyle() has the BOLD bit set. */
	bool isBold() const {
		return (style() & kBold) != 0;
	}

	/** Returns true if getStyle() has the ITALIC bit set. */
	bool isItalic() const {
		return (style() & kItalic) != 0;
	}

private:
	Style mStyle;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_TYPEFACE_H_ */
