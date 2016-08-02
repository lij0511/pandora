/*
 * LambertMaterial.cpp
 *
 *  Created on: 2016年6月23日
 *      Author: lijing
 */

#include "pola/graphic/material/LambertMaterial.h"

#include "pola/utils/StringBuffer.h"
#include <vector>

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
				break;
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
				break;
			}
			glUniform3f(u_dl, light->direction.x, light->direction.y, light->direction.z);
		}
	}

	if (lights && lights->pointLightCount() > 0) {
		static std::vector<utils::String> pointLightsColors;
		static std::vector<utils::String> pointLightsDistances;
		static std::vector<utils::String> pointLightsPositions;
		for (unsigned i = 0; i < lights->pointLightCount(); i ++) {
			PointLight* light = (PointLight*) lights->pointLight(i);
			GLint u_pl;

			utils::String color;
			if (i < pointLightsColors.size()) {
				color = pointLightsColors[i];
			} else {
				char buf[40];
				sprintf(buf, "u_pointLights[%u].color", i);
				color = buf;
				pointLightsColors.push_back(color);
			}
			if (!glProgram->fetchUniform(color, u_pl)) {
				break;
			}
			glUniform3f(u_pl, light->color.r, light->color.g, light->color.b);

			utils::String distance;
			if (i < pointLightsDistances.size()) {
				distance = pointLightsDistances[i];
			} else {
				char buf[40];
				sprintf(buf, "u_pointLights[%u].distance", i);
				distance = buf;
				pointLightsDistances.push_back(distance);
			}
			if (!glProgram->fetchUniform(distance, u_pl)) {
				break;
			}
			glUniform1f(u_pl, light->distance);

			utils::String position;
			if (i < pointLightsPositions.size()) {
				position = pointLightsPositions[i];
			} else {
				char buf[40];
				sprintf(buf, "u_pointLights[%u].position", i);
				position = buf;
				pointLightsPositions.push_back(position);
			}
			if (!glProgram->fetchUniform(position, u_pl)) {
				break;
			}
			glUniform3f(u_pl, light->position.x, light->position.y, light->position.z);
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

const utils::String LambertMaterial::generateVertexShader() {
	utils::StringBuffer sb;
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::VS_Para_TextureMap())
		.append(GLShaderLib::Para_Lighs())
		.append(STRINGIFY(
			varying vec3 v_light;
			void main()
			{\n
			 v_light = vec3( 0.0 );
			\n#if defined(NUM_DIR_LIGHTS) && (NUM_DIR_LIGHTS > 0)\n
			  DirectionalLight directionalLight;
			  for (int i = 0; i < NUM_DIR_LIGHTS; i ++) {
			    directionalLight = u_dirLights[ i ];
			    float dotNL = clamp(dot(a_normal, normalize(directionalLight.direction)), 0.0f, 1.0f);
			    v_light += directionalLight.color * dotNL;
			  }
			\n#endif\n
			\n#if defined(NUM_POINT_LIGHTS) && (NUM_POINT_LIGHTS > 0)\n
			  PointLight pointLight;
			  vec3 pos = (u_model * a_position).xyz;
			  for (int i = 0; i < NUM_POINT_LIGHTS; i ++) {
			    pointLight = u_pointLights[ i ];
			    vec3 dir = pointLight.position - pos;
			    float dis = length(dir);
			    if (dis > 0.0 && dis < pointLight.distance) {
			      float dotNL = clamp(dot(a_normal, normalize(dir)), 0.0f, 1.0f);
			      v_light += pointLight.color * dotNL * (pointLight.distance - dis) / pointLight.distance;
			    }
			  }
			\n#endif\n
			  v_light += u_ambientLight;
			))
		.append(GLShaderLib::VS_TextureMap())
		.append(GLShaderLib::VS_MainPosition())
		.append("}");
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
				STRINGIFY(
				uniform vec4 u_color;
				varying vec3 v_light;
				void main()
				{
			))
		.append(GLShaderLib::FS_DiffuseColor())
		.append("  diffuseColor = u_color;")
		.append(GLShaderLib::FS_TextureMap())
		.append(
			"  gl_FragColor = diffuseColor * vec4(v_light, 1.0);"
			"}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

} /* namespace graphic */
} /* namespace pola */
