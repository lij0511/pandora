/*
 * GLShaderLib.cpp
 *
 *  Created on: 2016年6月18日
 *      Author: lijing
 */

#include "pola/graphic/gl/GLShaderLib.h"

#ifndef STRINGIFY
#define STRINGIFY(A)  #A
#endif

namespace pola {
namespace graphic {

const char* GLShaderLib::VS_MainUnifroms() {
	return "uniform mat4 u_projection;"
			"uniform mat4 u_model;"
			"uniform mat4 u_view;"
			"uniform mat3 u_normal_matrix;";
}

const char* GLShaderLib::VS_MainAttributes() {
	return "attribute vec3 a_position;"
			"attribute vec2 a_uv;"
			"attribute vec3 a_normal;";
}

const char* GLShaderLib::VS_MainPosition() {
	return "  gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);";
}

const char* GLShaderLib::VS_Para_TextureMap() {
	return "\n#ifdef TEXTURE_MAP\n"
			"varying vec2 v_uv;"
			"\n#endif\n";
}

const char* GLShaderLib::VS_TextureMap() {
	return "\n#ifdef TEXTURE_MAP\n"
			"v_uv = a_uv;"
			"\n#endif\n";
}

const char* GLShaderLib::VS_Para_ShadowMap() {
	return STRINGIFY(
			\n#ifdef USE_SHADOW_MAP\n
			\n#if defined(NUM_DIR_LIGHTS) && (NUM_DIR_LIGHTS > 0)\n
				uniform mat4 u_directionalShadowMatrix[ NUM_DIR_LIGHTS ];
				varying vec4 v_directionalShadowCoord[ NUM_DIR_LIGHTS ];
			\n#endif\n
			\n#if defined(NUM_POINT_LIGHTS) && (NUM_POINT_LIGHTS > 0)\n
				uniform mat4 u_pointShadowMatrix[ NUM_POINT_LIGHTS ];
				varying vec4 v_pointShadowCoord[ NUM_POINT_LIGHTS ];
			\n#endif\n
			\n#if defined(NUM_SPOT_LIGHTS) && (NUM_SPOT_LIGHTS > 0)\n
				uniform mat4 u_spotShadowMatrix[ NUM_SPOT_LIGHTS ];
				varying vec4 v_spotShadowCoord[ NUM_SPOT_LIGHTS ];
			\n#endif\n
			\n#endif\n
		);
}

const char* GLShaderLib::VS_ShadowMap() {
	return STRINGIFY(
				\n#ifdef USE_SHADOW_MAP\n
				vec4 worldPosition =  u_model * vec4(a_position, 1.0);
				\n#if defined(NUM_DIR_LIGHTS) && (NUM_DIR_LIGHTS > 0)\n
				for ( int i = 0; i < NUM_DIR_LIGHTS; i ++ ) {
					v_directionalShadowCoord[ i ] = u_directionalShadowMatrix[ i ] * worldPosition;
				}
				\n#endif\n
				\n#if defined(NUM_POINT_LIGHTS) && (NUM_POINT_LIGHTS > 0)\n
				for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {
					v_pointShadowCoord[ i ] = u_pointShadowMatrix[ i ] * worldPosition;
				}
				\n#endif\n
				\n#if defined(NUM_SPOT_LIGHTS) && (NUM_SPOT_LIGHTS > 0)\n
				for ( int i = 0; i < NUM_SPOT_LIGHTS; i ++ ) {
					v_spotShadowCoord[ i ] = u_spotShadowMatrix[ i ] * worldPosition;
				}
				\n#endif\n
				\n#endif\n
	);
}

const char* GLShaderLib::FS_MainHeader() {
	return "\n#ifdef GL_ES\n"
			"\n#define LOWP lowp\n"
			"precision highp float;"
			"\n#else\n"
			"\n#define LOWP\n"
			"\n#endif\n";
}

const char* GLShaderLib::FS_DiffuseColor() {
	return "vec4 diffuseColor;\n";
}

const char* GLShaderLib::FS_Para_TextureMap() {
	return "\n#ifdef TEXTURE_MAP\n"
			"uniform sampler2D u_textureMap;"
			"varying vec2 v_uv;"
			"\n#endif\n";
}

const char* GLShaderLib::FS_TextureMap() {
	return "\n#ifdef TEXTURE_MAP\n"
			"	\n#ifdef TEXTURE_MAP_A8\n"
			"	diffuseColor *= texture2D(u_textureMap,  v_uv).a;"
			"	\n#else\n"
			"	diffuseColor *= texture2D(u_textureMap,  v_uv);"
			"	\n#endif\n"
			"\n#endif\n";
}

const char* GLShaderLib::FS_Para_ShadowMap() {
	return STRINGIFY(
			\n#ifdef USE_SHADOW_MAP\n

				\n#if defined(NUM_DIR_LIGHTS) && (NUM_DIR_LIGHTS > 0)\n

					uniform sampler2D directionalShadowMap[ NUM_DIR_LIGHTS ];
					varying vec4 v_directionalShadowCoord[ NUM_DIR_LIGHTS ];

					\n#endif\n

					\n#if defined(NUM_SPOT_LIGHTS) && (NUM_SPOT_LIGHTS > 0)\n

					uniform sampler2D spotShadowMap[ NUM_SPOT_LIGHTS ];
					varying vec4 v_spotShadowCoord[ NUM_SPOT_LIGHTS ];

					\n#endif\n

				\n#if defined(NUM_POINT_LIGHTS) && (NUM_POINT_LIGHTS > 0)\n

					uniform sampler2D pointShadowMap[ NUM_POINT_LIGHTS ];
					varying vec4 v_pointShadowCoord[ NUM_POINT_LIGHTS ];

					\n#endif\n

				float texture2DCompare( sampler2D depths, vec2 uv, float compare ) {

					return step( compare, unpackRGBAToDepth( texture2D( depths, uv ) ) );

				}

				float texture2DShadowLerp( sampler2D depths, vec2 size, vec2 uv, float compare ) {

					const vec2 offset = vec2( 0.0, 1.0 );

					vec2 texelSize = vec2( 1.0 ) / size;
					vec2 centroidUV = floor( uv * size + 0.5 ) / size;

					float lb = texture2DCompare( depths, centroidUV + texelSize * offset.xx, compare );
					float lt = texture2DCompare( depths, centroidUV + texelSize * offset.xy, compare );
					float rb = texture2DCompare( depths, centroidUV + texelSize * offset.yx, compare );
					float rt = texture2DCompare( depths, centroidUV + texelSize * offset.yy, compare );

					vec2 f = fract( uv * size + 0.5 );

					float a = mix( lb, lt, f.y );
					float b = mix( rb, rt, f.y );
					float c = mix( a, b, f.x );

					return c;

				}

				float getShadow( sampler2D shadowMap, vec2 shadowMapSize, float shadowBias, float shadowRadius, vec4 shadowCoord ) {

					shadowCoord.xyz /= shadowCoord.w;
					shadowCoord.z += shadowBias;

					// if ( something && something ) breaks ATI OpenGL shader compiler
					// if ( all( something, something ) ) using this instead

					bvec4 inFrustumVec = bvec4 ( shadowCoord.x >= 0.0, shadowCoord.x <= 1.0, shadowCoord.y >= 0.0, shadowCoord.y <= 1.0 );
					bool inFrustum = all( inFrustumVec );

					bvec2 frustumTestVec = bvec2( inFrustum, shadowCoord.z <= 1.0 );

					bool frustumTest = all( frustumTestVec );

					if ( inFrustum ) {

						\n#if defined( SHADOWMAP_TYPE_PCF )\n

						vec2 texelSize = vec2( 1.0 ) / shadowMapSize;

						float dx0 = - texelSize.x * shadowRadius;
						float dy0 = - texelSize.y * shadowRadius;
						float dx1 = + texelSize.x * shadowRadius;
						float dy1 = + texelSize.y * shadowRadius;

						return (
							texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx0, dy0 ), shadowCoord.z ) +
							texture2DCompare( shadowMap, shadowCoord.xy + vec2( 0.0, dy0 ), shadowCoord.z ) +
							texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx1, dy0 ), shadowCoord.z ) +
							texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx0, 0.0 ), shadowCoord.z ) +
							texture2DCompare( shadowMap, shadowCoord.xy, shadowCoord.z ) +
							texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx1, 0.0 ), shadowCoord.z ) +
							texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx0, dy1 ), shadowCoord.z ) +
							texture2DCompare( shadowMap, shadowCoord.xy + vec2( 0.0, dy1 ), shadowCoord.z ) +
							texture2DCompare( shadowMap, shadowCoord.xy + vec2( dx1, dy1 ), shadowCoord.z )
						) * ( 1.0 / 9.0 );

						\n#elif defined( SHADOWMAP_TYPE_PCF_SOFT )\n

						vec2 texelSize = vec2( 1.0 ) / shadowMapSize;

						float dx0 = - texelSize.x * shadowRadius;
						float dy0 = - texelSize.y * shadowRadius;
						float dx1 = + texelSize.x * shadowRadius;
						float dy1 = + texelSize.y * shadowRadius;

						return (
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx0, dy0 ), shadowCoord.z ) +
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( 0.0, dy0 ), shadowCoord.z ) +
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx1, dy0 ), shadowCoord.z ) +
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx0, 0.0 ), shadowCoord.z ) +
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy, shadowCoord.z ) +
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx1, 0.0 ), shadowCoord.z ) +
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx0, dy1 ), shadowCoord.z ) +
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( 0.0, dy1 ), shadowCoord.z ) +
							texture2DShadowLerp( shadowMap, shadowMapSize, shadowCoord.xy + vec2( dx1, dy1 ), shadowCoord.z )
						) * ( 1.0 / 9.0 );

						\n#else\n // no percentage-closer filtering:\n

						return texture2DCompare( shadowMap, shadowCoord.xy, shadowCoord.z );

						\n#endif\n

					}

					return 1.0;

				}

				// cubeToUV() maps a 3D direction vector suitable for cube texture mapping to a 2D
				// vector suitable for 2D texture mapping. This code uses the following layout for the
				// 2D texture:
				//
				// xzXZ
				//  y Y
				//
				// Y - Positive y direction
				// y - Negative y direction
				// X - Positive x direction
				// x - Negative x direction
				// Z - Positive z direction
				// z - Negative z direction
				//
				// Source and test bed:
				// https://gist.github.com/tschw/da10c43c467ce8afd0c4

				vec2 cubeToUV( vec3 v, float texelSizeY ) {

					// Number of texels to avoid at the edge of each square

					vec3 absV = abs( v );

					// Intersect unit cube

					float scaleToCube = 1.0 / max( absV.x, max( absV.y, absV.z ) );
					absV *= scaleToCube;

					// Apply scale to avoid seams

					// two texels less per square (one texel will do for NEAREST)
					v *= scaleToCube * ( 1.0 - 2.0 * texelSizeY );

					// Unwrap

					// space: -1 ... 1 range for each square
					//
					// #X##		dim    := ( 4 , 2 )
					//  # #		center := ( 1 , 1 )

					vec2 planar = v.xy;

					float almostATexel = 1.5 * texelSizeY;
					float almostOne = 1.0 - almostATexel;

					if ( absV.z >= almostOne ) {

						if ( v.z > 0.0 )
							planar.x = 4.0 - v.x;

					} else if ( absV.x >= almostOne ) {

						float signX = sign( v.x );
						planar.x = v.z * signX + 2.0 * signX;

					} else if ( absV.y >= almostOne ) {

						float signY = sign( v.y );
						planar.x = v.x + 2.0 * signY + 2.0;
						planar.y = v.z * signY - 2.0;

					}

					// Transform to UV space

					// scale := 0.5 / dim
					// translate := ( center + 0.5 ) / dim
					return vec2( 0.125, 0.25 ) * planar + vec2( 0.375, 0.75 );

				}

				float getPointShadow( sampler2D shadowMap, vec2 shadowMapSize, float shadowBias, float shadowRadius, vec4 shadowCoord ) {

					vec2 texelSize = vec2( 1.0 ) / ( shadowMapSize * vec2( 4.0, 2.0 ) );

					// for point lights, the uniform @vShadowCoord is re-purposed to hold
					// the distance from the light to the world-space position of the fragment.
					vec3 lightToPosition = shadowCoord.xyz;

					// bd3D = base direction 3D
					vec3 bd3D = normalize( lightToPosition );
					// dp = distance from light to fragment position
					float dp = ( length( lightToPosition ) - shadowBias ) / 1000.0;

					\n#if defined( SHADOWMAP_TYPE_PCF ) || defined( SHADOWMAP_TYPE_PCF_SOFT )\n

						vec2 offset = vec2( - 1, 1 ) * shadowRadius * texelSize.y;

						return (
							texture2DCompare( shadowMap, cubeToUV( bd3D + offset.xyy, texelSize.y ), dp ) +
							texture2DCompare( shadowMap, cubeToUV( bd3D + offset.yyy, texelSize.y ), dp ) +
							texture2DCompare( shadowMap, cubeToUV( bd3D + offset.xyx, texelSize.y ), dp ) +
							texture2DCompare( shadowMap, cubeToUV( bd3D + offset.yyx, texelSize.y ), dp ) +
							texture2DCompare( shadowMap, cubeToUV( bd3D, texelSize.y ), dp ) +
							texture2DCompare( shadowMap, cubeToUV( bd3D + offset.xxy, texelSize.y ), dp ) +
							texture2DCompare( shadowMap, cubeToUV( bd3D + offset.yxy, texelSize.y ), dp ) +
							texture2DCompare( shadowMap, cubeToUV( bd3D + offset.xxx, texelSize.y ), dp ) +
							texture2DCompare( shadowMap, cubeToUV( bd3D + offset.yxx, texelSize.y ), dp )
						) * ( 1.0 / 9.0 );

						\n#else\n // no percentage-closer filtering

						return texture2DCompare( shadowMap, cubeToUV( bd3D, texelSize.y ), dp );

					\n#endif\n

				}

				\n#endif\n

				float getShadowMask() {

					float shadow = 1.0;

					\n#ifdef USE_SHADOW_MAP\n

					\n#if defined(NUM_DIR_LIGHTS) && (NUM_DIR_LIGHTS > 0)\n

					DirectionalLight directionalLight;

					for ( int i = 0; i < NUM_DIR_LIGHTS; i ++ ) {

						directionalLight = u_dirLights[ i ];
						shadow *= bool( directionalLight.shadow ) ? getShadow( directionalShadowMap[ i ], directionalLight.shadowMapSize, directionalLight.shadowBias, directionalLight.shadowRadius, v_directionalShadowCoord[ i ] ) : 1.0;

					}

					\n#endif\n

					\n#if defined(NUM_SPOT_LIGHTS) && (NUM_SPOT_LIGHTS > 0)\n

					SpotLight spotLight;

					for ( int i = 0; i < NUM_SPOT_LIGHTS; i ++ ) {

						spotLight = u_spotLights[ i ];
						shadow *= bool( spotLight.shadow ) ? getShadow( spotShadowMap[ i ], spotLight.shadowMapSize, spotLight.shadowBias, spotLight.shadowRadius, v_spotShadowCoord[ i ] ) : 1.0;

					}

					\n#endif\n

					\n#if defined(NUM_POINT_LIGHTS) && (NUM_POINT_LIGHTS > 0)\n

					PointLight pointLight;

					for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {

						pointLight = u_pointLights[ i ];
						shadow *= bool( pointLight.shadow ) ? getPointShadow( pointShadowMap[ i ], pointLight.shadowMapSize, pointLight.shadowBias, pointLight.shadowRadius, v_pointShadowCoord[ i ] ) : 1.0;

					}
					\n#endif\n

					\n#endif\n

					return shadow;

				}
		);
}

const char* GLShaderLib::Para_Packing() {
	return STRINGIFY(
			vec4 packDepthToRGBA( const in float value ) {
				const vec4 bit_shift = vec4( 256.0 * 256.0 * 256.0, 256.0 * 256.0, 256.0, 1.0 );
				const vec4 bit_mask = vec4( 0.0, 1.0 / 256.0, 1.0 / 256.0, 1.0 / 256.0 );
				vec4 res = mod( value * bit_shift * vec4( 255 ), vec4( 256 ) ) / vec4( 255 );
				res -= res.xxyz * bit_mask;
				return res;
			}
			float unpackRGBAToDepth( const in vec4 rgba ) {
				const vec4 bitSh = vec4( 1.0 / ( 256.0 * 256.0 * 256.0 ), 1.0 / ( 256.0 * 256.0 ), 1.0 / 256.0, 1.0 );
				return dot( rgba, bitSh );
			}
		);
}

const char* GLShaderLib::Para_Lighs() {
	/*"struct BlinnPhongMaterial {\n"
				"vec3	diffuseColor;\n"
				"vec3	specularColor;\n"
				"float	specularShininess;\n"
				"float	specularStrength;\n"
				"};\n"*/
	return STRINGIFY(
			uniform vec3 u_ambientLight;
			\n#if defined(NUM_DIR_LIGHTS) && (NUM_DIR_LIGHTS > 0)\n
			struct DirectionalLight {
			vec3 direction;
			vec3 color;

			int shadow;
			float shadowBias;
			float shadowRadius;
			vec2 shadowMapSize;
			};
			uniform DirectionalLight u_dirLights[NUM_DIR_LIGHTS];
			\n#endif\n
			\n#if defined(NUM_POINT_LIGHTS) && (NUM_POINT_LIGHTS > 0)\n
			struct PointLight {
			vec3 position;
			vec3 color;
			float distance;

			int shadow;
			float shadowBias;
			float shadowRadius;
			vec2 shadowMapSize;
			};
			uniform PointLight u_pointLights[NUM_POINT_LIGHTS];
			\n#endif\n
			\n#if defined(NUM_SPOT_LIGHTS) && (NUM_SPOT_LIGHTS > 0)\n
			struct SpotLight {
			vec3 position;
			vec3 direction;
			vec3 color;
			float angle;
			float distance;

			int shadow;
			float shadowBias;
			float shadowRadius;
			vec2 shadowMapSize;
			};
			uniform SpotLight u_spotLights[NUM_SPOT_LIGHTS];
			\n#endif\n
			);
}

} /* namespace graphic */
} /* namespace pola */
