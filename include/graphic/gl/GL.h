/*
 * GL.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_GL_H_
#define POLA_GRAPHIC_GL_H_

/* TODO 需要更好的宏 */
#ifdef __arm__
#define GLES 2
#include <GLES2/gl2.h>
#else
#include <GL/glew.h>
#endif


#endif /* POLA_GRAPHIC_GL_H_ */