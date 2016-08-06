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

	static const char* VS_Para_TextureMap();
	static const char* VS_TextureMap();

	static const char* VS_Para_ShadowMap();
	static const char* VS_ShadowMap();

	static const char* FS_MainHeader();
	static const char* FS_DiffuseColor();
	static const char* FS_TextureMap();
	static const char* FS_Para_TextureMap();

	static const char* FS_Para_ShadowMap();

	static const char* Para_Packing();

	/* lights */
	static const char* Para_Lighs();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLSHADERLIB_H_ */
