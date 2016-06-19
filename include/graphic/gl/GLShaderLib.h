/*
 * GLShaderLib.h
 *
 *  Created on: 2016年6月18日
 *      Author: lijing
 */

#ifndef POLA_GLSHADERLIB_H_
#define POLA_GLSHADERLIB_H_

namespace pola {
namespace graphic {

class GLShaderLib {
public:
	static const char* VS_MainUnifroms();
	static const char* VS_MainAttributes();

	static const char* VS_MainPosition();

	static const char* FS_MainHeader();


	/* lights */
	static const char* FS_Para_Lighs();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLSHADERLIB_H_ */
