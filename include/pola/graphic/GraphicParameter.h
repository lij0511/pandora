/*
 * GraphicParameter.h
 *
 *  Created on: 2016年7月15日
 *      Author: lijing
 */

#ifndef POLA_GRAPHICPARAMETER_H_
#define POLA_GRAPHICPARAMETER_H_

namespace pola {
namespace graphic {

struct GraphicParameter {
	enum DrawMode {
		POINTS,

		LINES,
		LINE_LOOP,
		LINE_STRIP,

		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
	};

	DrawMode drawMode;
	float lineWidth;

	GraphicParameter(DrawMode drawMode = TRIANGLES, float lineWidth = 1.f);
};

inline GraphicParameter::GraphicParameter(DrawMode drawMode, float lineWidth) {
	this->drawMode = drawMode;
	this->lineWidth = lineWidth;
}

}
}

#endif /* POLA_GRAPHICPARAMETER_H_ */
