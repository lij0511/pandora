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

			uniform = glProgram->fetchUniform("u_dirLights", i, "shadow");
			if (uniform == nullptr) {
				break;
			}
			glUniform1i(uniform->location, light->castShadow ? 1 : 0);

			if (light->castShadow) {
				uniform = glProgram->fetchUniform("u_dirLights", i, "shadowBias");
				if (uniform == nullptr) {
					break;
				}
				glUniform1i(uniform->location, 0);

				uniform = glProgram->fetchUniform("u_dirLights", i, "shadowRadius");
				if (uniform == nullptr) {
					break;
				}
				glUniform1i(uniform->location, 1);

				uniform = glProgram->fetchUniform("u_dirLights", i, "shadowMapSize");
				if (uniform == nullptr) {
					break;
				}
				glUniform2f(uniform->location, float(light->mapSize.width), float(light->mapSize.height));

				uniform = glProgram->fetchUniform("u_directionalShadowMatrix", i);
				if (uniform == nullptr) {
					break;
				}
				glUniformMatrix4fv(uniform->location, 1, GL_FALSE, &light->matrix[0]);

				if (light->map != nullptr) {
					GLCaches& cache = GLCaches::get();
					cache.activeTexture(cache.activeTexture() + 1);
					GLTexture* texture = ((GLRenderTarget*) light->map)->getTexture();
					cache.bindTexture(texture->id);

					uniform = glProgram->fetchUniform("directionalShadowMap", i);
					if (uniform == nullptr) {
						break;
					}
					glUniform1i(uniform->location, cache.activeTexture());
				}
			}
		}
	}

	if (lights && lights->pointLightCount() > 0) {
		for (unsigned i = 0; i < lights->pointLightCount(); i ++) {
			PointLight* light = (PointLight*) lights->pointLight(i);

			GLUniform* uniform = glProgram->fetchUniform("u_pointLights", i, "color");
			if (uniform == nullptr) {
				break;
			}
			glUniform3f(uniform->location, light->color.r, light->color.g, light->color.b);

			uniform = glProgram->fetchUniform("u_pointLights", i, "distance");
			if (uniform == nullptr) {
				break;
			}
			glUniform1f(uniform->location, light->distance);

			uniform = glProgram->fetchUniform("u_pointLights", i, "position");
			if (uniform == nullptr) {
				break;
			}
			glUniform3f(uniform->location, light->position.x, light->position.y, light->position.z);
		}
	}

	GLUniform* uniform = glProgram->fetchUniform("u_ambientLight");
	if (uniform != nullptr) {
		FColor3 ambient = lights->ambientLight();
		glUniform3f(uniform->location, ambient.r, ambient.g, ambient.b);
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
