/*
 * PhongMaterial.cpp
 *
 *  Created on: 2016年6月19日
 *      Author: lijing
 */

#include "pola/graphic/material/PhongMaterial.h"

#include "pola/utils/StringBuffer.h"
#include <vector>

#ifdef OGL_RENDERER
#include "pola/graphic/gl/GLProgram.h"
#include "pola/graphic/gl/GLShaderLib.h"
#include "pola/graphic/gl/GLTexture.h"
#include "pola/graphic/gl/GLRenderTarget.h"
#include "pola/graphic/gl/GLCaches.h"
#endif

namespace pola {
namespace graphic {

PhongMaterial::PhongMaterial(const FColor4& color, Texture* textureMap) : Material(color, textureMap) {
}

PhongMaterial::~PhongMaterial() {
}

void PhongMaterial::bind(GraphicContext* graphic, Program* program) {
	Material::bind(graphic, program);
#ifdef OGL_RENDERER
	const Lights* lights = graphic->lights();
	GLProgram* glProgram = (GLProgram*) program;
	if (lights && lights->directionalLightCount() > 0) {
		for (unsigned i = 0; i < lights->directionalLightCount(); i ++) {
			DirectionalLight* light = (DirectionalLight*) lights->directionalLight(i);

			GLUniform* uniform = glProgram->fetchUniform("u_dirLights", i, "color");
			if (uniform == nullptr) {
				break;
			}
			glUniform3f(uniform->location, light->color.r, light->color.g, light->color.b);

			uniform = glProgram->fetchUniform("u_dirLights", i, "direction");
			if (uniform == nullptr) {
				break;
			}
			glUniform3f(uniform->location, light->direction.x, light->direction.y, light->direction.z);

		}
	}

	GLUniform* uniform = glProgram->fetchUniform("u_ambientLight");
	if (uniform != nullptr) {
		FColor3 ambient = lights->ambientLight();
		glUniform3f(uniform->location, ambient.r, ambient.g, ambient.b);
	}
#endif
}

const utils::String PhongMaterial::generateVertexShader() {
	utils::StringBuffer sb;
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::VS_Para_TextureMap())
		.append("varying vec3 v_normal;"
			"void main()"
			"{")
		.append(GLShaderLib::VS_TextureMap())
		.append(GLShaderLib::VS_MainPosition())
		.append("  v_normal = a_normal;");
	sb.append("}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

const utils::String PhongMaterial::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader())
		.append(GLShaderLib::Para_Lighs())
		.append(GLShaderLib::FS_Para_TextureMap())
		.append("varying vec3 v_normal;"
			"uniform vec4 u_color;"
			"void main()"
			"{"
			"  vec3 normal = normalize(v_normal);")
		.append(GLShaderLib::FS_DiffuseColor())
		.append("  diffuseColor = u_color;\n")
		.append(GLShaderLib::FS_TextureMap())
		.append(
			"  vec3 outgoing = vec3(0.0f, 0.0f, 0.0f);"
			"\n#if (NUM_DIR_LIGHTS > 0)\n"
			"  DirectionalLight directionalLight;"
			"  for (int i = 0; i < NUM_DIR_LIGHTS; i ++) {"
			"    directionalLight = u_dirLights[ i ];"
			"    float dotNL = clamp(dot(normal, directionalLight.direction), 0.0f, 1.0f);"
			"    outgoing += directionalLight.color * dotNL * diffuseColor.rgb;"
			"  }"
			"\n#endif\n"
			"  outgoing += u_ambientLight * diffuseColor.rgb;"
			"  gl_FragColor = vec4(outgoing, diffuseColor.a);"
			"}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

} /* namespace graphic */
} /* namespace pola */
