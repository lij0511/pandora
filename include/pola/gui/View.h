/*
 * View.h
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "pola/graphic/GraphicContext.h"

namespace pola {
namespace gui {

/*
 *
 */
class View {
public:
	View();
	virtual ~View();

protected:
	virtual void onDraw(graphic::GraphicContext* graphic);
};

} /* namespace gui */
} /* namespace pola */

#endif /* VIEW_H_ */
