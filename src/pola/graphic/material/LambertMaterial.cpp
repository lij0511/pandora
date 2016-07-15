/*
 * LambertMaterial.cpp
 *
 *  Created on: 2016年6月23日
 *      Author: lijing
 */

#include "pola/graphic/material/LambertMaterial.h"

#include "pola/utils/StringBuffer.h"

namespace pola {
namespace graphic {

LambertMaterial::LambertMaterial(const FColor4& color, Texture* textureMap) : Material(color, textureMap) {
}

LambertMaterial::~LambertMaterial() {
}

void LambertMaterial::bind(GraphicContext* graphic, Program* program) {
	Material::bind(graphic, program);
#ifdef OGL_RENDERER
	const Lights* lights = graphic->lights();
	GLProgram* glProgram = (GLProgram*) program;
	if (lights && lights->directionalLightCount() > 0) {
		static utils::Vector<utils::String> dirLightsColors;
		static utils::Vector<utils::String> dirLightsDirections;
		for (unsigned i = 0; i < lights->directionalLightCount(); i ++) {
			DirectionalLight* light = (DirectionalLight*) lights->directionalLight(i);
			GLint u_dl;

			utils::String color;
			if (i < dirLightsColors.size()) {
				color = dirLightsColors[i];
			} else {
				char buf[40];
				sprintf(buf, "u_dirLights[%u].color", i);
				color = buf;
				dirLightsColors.push(color);
			}
			if (!glProgram->fetchUniform(color, u_dl)) {
				return;
			}
			glUniform3f(u_dl, light->color.r, light->color.g, light->color.b);

			utils::String direction;
			if (i < dirLightsDirections.size()) {
				direction = dirLightsDirections[i];
			} else {
				char buf[40];
				sprintf(buf, "u_dirLights[%u].direction", i);
				direction = buf;
				dirLightsDirections.push(direction);
			}
			if (!glProgram->fetchUniform(direction, u_dl)) {
				return;
			}
			glUniform3f(u_dl, light->direction.x, light->direction.y, light->direction.z);
		}
	}

	GLint u_ambientLight;
	if (glProgram->fetchUniform(utils::String("u_ambientLight", true), u_ambientLight)) {
		FColor3 ambient = lights->ambientLight();
		glUniform3f(u_ambientLight, ambient.r, ambient.g, ambient.b);
	}
#endif
}

const utils::String LambertMaterial::generateVertexShader() {
	utils::StringBuffer sb;
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::VS_Para_TextureMap())
		.append(GLShaderLib::Para_Lighs())
		.append(
			"varying vec3 v_light;\n"
			"void main()\n"
			"{\n"
			" v_light = vec3( 0.0 );\n"
			"#if defined(NUM_DIR_LIGHTS) && NUM_DIR_LIGHTS > 0\n"
			"  DirectionalLight directionalLight;\n"
			"  for (int i = 0; i < NUM_DIR_LIGHTS; i ++) {\n"
			"    directionalLight = u_dirLights[ i ];\n"
			"    float dotNL = clamp(dot(a_normal, directionalLight.direction), 0.0f, 1.0f);\n"
			"    v_light += directionalLight.color * dotNL;\n"
			"  }\n"
			"  v_light += u_ambientLight;\n"
			"#endif\n")
		.append(GLShaderLib::VS_TextureMap())
		.append(GLShaderLib::VS_MainPosition())
		.append("}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

const utils::String LambertMaterial::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader())
		.append(GLShaderLib::FS_Para_TextureMap())
		.append(
			"uniform vec4 u_color;\n"
			"varying vec3 v_light;\n"
			"void main()\n"
			"{\n")
		.append(GLShaderLib::FS_DiffuseColor())
		.append("  diffuseColor = u_color;\n")
		.append(GLShaderLib::FS_TextureMap())
		.append(
			"  gl_FragColor = diffuseColor * vec4(v_light, 1.0);\n"
			"}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

} /* namespace graphic */
} /* namespace pola */
