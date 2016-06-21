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
			"  vec3 normal = normalize(v_normal);\n"
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
			"  outgoing += u_ambientLight * diffuseColor.rgb;\n"
			"  gl_FragColor = vec4(outgoing, diffuseColor.a);\n"
			"}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

} /* namespace graphic */
} /* namespace pola */
