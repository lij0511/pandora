/*
 * PhongMaterial.cpp
 *
 *  Created on: 2016年6月19日
 *      Author: lijing
 */

#include "pola/graphic/material/PhongMaterial.h"

#include "pola/utils/StringBuffer.h"
#include <vector>

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
		static std::vector<utils::String> dirLightsColors;
		static std::vector<utils::String> dirLightsDirections;
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
				dirLightsColors.push_back(color);
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
				dirLightsDirections.push_back(direction);
			}
			if (!glProgram->fetchUniform(direction, u_dl)) {
				return;
			}
			glUniform3f(u_dl, light->direction.x, light->direction.y, light->direction.z);
		}
	}

	GLint u_ambientLight;
	static utils::String ambientLight("u_ambientLight");
	if (glProgram->fetchUniform(ambientLight, u_ambientLight)) {
		FColor3 ambient = lights->ambientLight();
		glUniform3f(u_ambientLight, ambient.r, ambient.g, ambient.b);
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
