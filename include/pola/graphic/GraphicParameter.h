/*
 * GraphicParameter.h
 *
 *  Created on: 2016年7月15日
 *      Author: lijing
 */

#ifndef POLA_GRAPHICPARAMETER_H_
#define POLA_GRAPHICPARAMETER_H_

#if defined(POLA_GLES) || defined(POLA_GL)
#include "pola/graphic/gl/GL.h"
#endif

namespace pola {
namespace graphic {

struct GraphicParameter {
	enum DrawMode {
#if defined(POLA_GLES) || defined(POLA_GL)
		POINTS									= GL_POINTS,

		LINES									= GL_LINES,
		LINE_LOOP							= GL_LINE_LOOP,
		LINE_STRIP							= GL_LINE_STRIP,

		TRIANGLES							= GL_TRIANGLES,
		TRIANGLE_STRIP				= GL_TRIANGLE_STRIP,
		TRIANGLE_FAN					= GL_TRIANGLE_FAN,
#else
		POINTS,

		LINES,
		LINE_LOOP,
		LINE_STRIP,

		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
#endif
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
