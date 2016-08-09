/*
 * LambertMaterial.cpp
 *
 *  Created on: 2016年6月23日
 *      Author: lijing
 */

#include "pola/graphic/material/LambertMaterial.h"

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
		static std::vector<utils::String> dirLightsShadows;
		static std::vector<utils::String> dirLightsShadowBias;
		static std::vector<utils::String> dirLightsShadowRadius;
		static std::vector<utils::String> dirLightsShadowMapSize;

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
			GLUniform* uniform = glProgram->fetchUniform("u_dirLights", i, "direction");
			if (uniform == nullptr) {
				break;
			}
			glUniform3f(uniform->location, light->direction.x, light->direction.y, light->direction.z);

			utils::String shadow;
			if (i < dirLightsShadows.size()) {
				shadow = dirLightsShadows[i];
			} else {
				char buf[40];
				sprintf(buf, "u_dirLights[%u].shadow", i);
				shadow = buf;
				dirLightsShadows.push_back(shadow);
			}
			if (!glProgram->fetchUniform(shadow, u_dl)) {
				break;
			}
			glUniform1i(u_dl, light->castShadow ? 1 : 0);

			if (light->castShadow) {
				utils::String shadowBias;
				if (i < dirLightsShadowBias.size()) {
					shadowBias = dirLightsShadowBias[i];
				} else {
					char buf[40];
					sprintf(buf, "u_dirLights[%u].shadowBias", i);
					shadowBias = buf;
					dirLightsShadowBias.push_back(shadowBias);
				}
				if (!glProgram->fetchUniform(shadowBias, u_dl)) {
					break;
				}
				glUniform1f(u_dl, 0);

				utils::String shadowRadius;
				if (i < dirLightsShadowRadius.size()) {
					shadowRadius = dirLightsShadowRadius[i];
				} else {
					char buf[40];
					sprintf(buf, "u_dirLights[%u].shadowRadius", i);
					shadowRadius = buf;
					dirLightsShadowRadius.push_back(shadowRadius);
				}
				if (!glProgram->fetchUniform(shadowRadius, u_dl)) {
					break;
				}
				glUniform1f(u_dl, 1);

				utils::String shadowMapSize;
				if (i < dirLightsShadowMapSize.size()) {
					shadowMapSize = dirLightsShadowMapSize[i];
				} else {
					char buf[40];
					sprintf(buf, "u_dirLights[%u].shadowMapSize", i);
					shadowMapSize = buf;
					dirLightsShadowMapSize.push_back(shadowMapSize);
				}
				if (!glProgram->fetchUniform(shadowMapSize, u_dl)) {
					break;
				}
				glUniform2f(u_dl, float(light->mapSize.width), float(light->mapSize.height));

				static utils::String shadowMatrix("u_directionalShadowMatrix[0]");
				if (!glProgram->fetchUniform(shadowMatrix, u_dl)) {
					break;
				}
				glUniformMatrix4fv(u_dl, 1, GL_FALSE, &light->matrix[0]);
				if (light->map != nullptr) {
					GLCaches& cache = GLCaches::get();
					cache.activeTexture(cache.activeTexture() + 1);
					GLTexture* texture = ((GLRenderTarget*) light->map)->getTexture();
					cache.bindTexture(texture->id);
					GLProgram* glProgram = (GLProgram*) program;
					static utils::String shadowMap("directionalShadowMap[0]");
					GLint u_textureMapH;
					if (glProgram->fetchUniform(shadowMap, u_textureMapH)) {
						glUniform1i(u_textureMapH, cache.activeTexture());
					}
				}
			}
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
		.append(GLShaderLib::VS_Para_ShadowMap())
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
			    float dotNL = clamp(dot(a_normal, - normalize(directionalLight.direction)), 0.0f, 1.0f);
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
			))
		.append(GLShaderLib::VS_TextureMap())
		.append(GLShaderLib::VS_ShadowMap())
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
	sb.append(GLShaderLib::Para_Packing())
		.append(GLShaderLib::FS_MainHeader())
		.append(GLShaderLib::FS_Para_TextureMap())
		.append(GLShaderLib::Para_Lighs())
		.append(GLShaderLib::FS_Para_ShadowMap())
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
			"  vec3 light = v_light * getShadowMask() + u_ambientLight;"
			"  light = clamp(light, vec3(0.0), vec3(1.0));"
			"  gl_FragColor = diffuseColor * vec4(light, 1.0);"
			"}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

} /* namespace graphic */
} /* namespace pola */
