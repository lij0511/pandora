/*
 * TPhongMaterial.cpp
 *
 *  Created on: 2016年6月19日
 *      Author: lijing
 */

#include "graphic/material/TPhongMaterial.h"
#ifdef OGL_RENDERER
#include "graphic/gl/GLProgram.h"
#include "graphic/gl/GLShaderLib.h"
#include "graphic/gl/GLTexture.h"
#include "graphic/gl/GLCaches.h"
#endif

#include "utils/StringBuffer.h"

namespace pola {
namespace graphic {

TPhongMaterial::TPhongMaterial(Texture* texture) : TMaterial(texture) {
}

TPhongMaterial::~TPhongMaterial() {
}

void TPhongMaterial::bind(GraphicContext* graphic, Program* program) {
	TMaterial::bind(graphic, program);
#ifdef OGL_RENDERER
	const Lights* lights = graphic->lights();
	if (lights && lights->directionalLightCount() > 0) {
		for (unsigned i = 0; i < lights->directionalLightCount(); i ++) {
			GLProgram* glProgram = (GLProgram*) program;
			DirectionalLight* light = (DirectionalLight*) lights->directionalLight(i);
			GLint u_dl;
			if (!glProgram->fetchUniform("u_dirLights[0].color", u_dl)) {
				return;
			}
			glUniform3f(u_dl, light->color.r, light->color.g, light->color.b);
			if (!glProgram->fetchUniform("u_dirLights[0].direction", u_dl)) {
				return;
			}
			glUniform3f(u_dl, light->direction.x, light->direction.y, light->direction.z);
		}
	}
#endif
}

const utils::String TPhongMaterial::generateVertexShader() {
	utils::StringBuffer sb;
#ifdef OGL_RENDERER
	sb.append("varying vec2 v_uv;\n"
			"varying vec3 v_normal;\n"
			"void main()\n"
			"{\n"
			"  v_uv = a_uv;\n"
			"  v_normal = a_normal;\n");
	sb.append(GLShaderLib::VS_MainPosition());
	sb.append("}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

const utils::String TPhongMaterial::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader());
	sb.append(GLShaderLib::FS_Para_Lighs());
	sb.append("uniform sampler2D u_texture;\n"
			"varying vec2 v_uv;\n"
			"varying vec3 v_normal;\n"
			"void main()\n"
			"{\n"
			"  vec3 normal = normalize( v_normal );\n"
			"  vec4 diffuseColor =texture2D(u_texture,  v_uv);\n"
			"  vec3 outgoing = vec3(0.0f, 0.0f, 0.0f);\n"
			"#if defined(NUM_DIR_LIGHTS) && NUM_DIR_LIGHTS > 0\n"
			"  DirectionalLight directionalLight;\n"
			"  for (int i = 0; i < NUM_DIR_LIGHTS; i ++) {\n"
			"    directionalLight = u_dirLights[ i ];\n"
			"    float dotNL = clamp(dot(normal, directionalLight.direction), 0.0f, 1.0f);\n"
			"    outgoing += directionalLight.color * dotNL * diffuseColor.rgb;\n"
			"  }\n"
			"#endif\n"
			"  gl_FragColor = vec4(outgoing, diffuseColor.a);\n"
			"}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

} /* namespace graphic */
} /* namespace pola */
