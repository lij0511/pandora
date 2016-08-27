/*
 * MD2MeshLoader.cpp
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#include <stdint.h>

//#define USE_MD2_MESH

#include "pola/log/Log.h"
#include "pola/scene/mesh/MD2MeshLoader.h"
#include "pola/scene/mesh/Mesh.h"
#ifdef USE_MD2_MESH
#include "pola/scene/mesh/MD2AnimatedMesh.h"
#endif

#include <string.h>

namespace pola {
namespace scene {

const int32_t MD2_MAGIC_NUMBER  = 844121161;
const int32_t MD2_VERSION       = 8;
const int32_t MD2_MAX_VERTS     = 2048;

const int32_t Q2_VERTEX_NORMAL_TABLE_SIZE = 162;
static const float Q2_VERTEX_NORMAL_TABLE[Q2_VERTEX_NORMAL_TABLE_SIZE][3] = {
	{-0.525731f, 0.000000f, 0.850651f},
	{-0.442863f, 0.238856f, 0.864188f},
	{-0.295242f, 0.000000f, 0.955423f},
	{-0.309017f, 0.500000f, 0.809017f},
	{-0.162460f, 0.262866f, 0.951056f},
	{0.000000f, 0.000000f, 1.000000f},
	{0.000000f, 0.850651f, 0.525731f},
	{-0.147621f, 0.716567f, 0.681718f},
	{0.147621f, 0.716567f, 0.681718f},
	{0.000000f, 0.525731f, 0.850651f},
	{0.309017f, 0.500000f, 0.809017f},
	{0.525731f, 0.000000f, 0.850651f},
	{0.295242f, 0.000000f, 0.955423f},
	{0.442863f, 0.238856f, 0.864188f},
	{0.162460f, 0.262866f, 0.951056f},
	{-0.681718f, 0.147621f, 0.716567f},
	{-0.809017f, 0.309017f, 0.500000f},
	{-0.587785f, 0.425325f, 0.688191f},
	{-0.850651f, 0.525731f, 0.000000f},
	{-0.864188f, 0.442863f, 0.238856f},
	{-0.716567f, 0.681718f, 0.147621f},
	{-0.688191f, 0.587785f, 0.425325f},
	{-0.500000f, 0.809017f, 0.309017f},
	{-0.238856f, 0.864188f, 0.442863f},
	{-0.425325f, 0.688191f, 0.587785f},
	{-0.716567f, 0.681718f, -0.147621f},
	{-0.500000f, 0.809017f, -0.309017f},
	{-0.525731f, 0.850651f, 0.000000f},
	{0.000000f, 0.850651f, -0.525731f},
	{-0.238856f, 0.864188f, -0.442863f},
	{0.000000f, 0.955423f, -0.295242f},
	{-0.262866f, 0.951056f, -0.162460f},
	{0.000000f, 1.000000f, 0.000000f},
	{0.000000f, 0.955423f, 0.295242f},
	{-0.262866f, 0.951056f, 0.162460f},
	{0.238856f, 0.864188f, 0.442863f},
	{0.262866f, 0.951056f, 0.162460f},
	{0.500000f, 0.809017f, 0.309017f},
	{0.238856f, 0.864188f, -0.442863f},
	{0.262866f, 0.951056f, -0.162460f},
	{0.500000f, 0.809017f, -0.309017f},
	{0.850651f, 0.525731f, 0.000000f},
	{0.716567f, 0.681718f, 0.147621f},
	{0.716567f, 0.681718f, -0.147621f},
	{0.525731f, 0.850651f, 0.000000f},
	{0.425325f, 0.688191f, 0.587785f},
	{0.864188f, 0.442863f, 0.238856f},
	{0.688191f, 0.587785f, 0.425325f},
	{0.809017f, 0.309017f, 0.500000f},
	{0.681718f, 0.147621f, 0.716567f},
	{0.587785f, 0.425325f, 0.688191f},
	{0.955423f, 0.295242f, 0.000000f},
	{1.000000f, 0.000000f, 0.000000f},
	{0.951056f, 0.162460f, 0.262866f},
	{0.850651f, -0.525731f, 0.000000f},
	{0.955423f, -0.295242f, 0.000000f},
	{0.864188f, -0.442863f, 0.238856f},
	{0.951056f, -0.162460f, 0.262866f},
	{0.809017f, -0.309017f, 0.500000f},
	{0.681718f, -0.147621f, 0.716567f},
	{0.850651f, 0.000000f, 0.525731f},
	{0.864188f, 0.442863f, -0.238856f},
	{0.809017f, 0.309017f, -0.500000f},
	{0.951056f, 0.162460f, -0.262866f},
	{0.525731f, 0.000000f, -0.850651f},
	{0.681718f, 0.147621f, -0.716567f},
	{0.681718f, -0.147621f, -0.716567f},
	{0.850651f, 0.000000f, -0.525731f},
	{0.809017f, -0.309017f, -0.500000f},
	{0.864188f, -0.442863f, -0.238856f},
	{0.951056f, -0.162460f, -0.262866f},
	{0.147621f, 0.716567f, -0.681718f},
	{0.309017f, 0.500000f, -0.809017f},
	{0.425325f, 0.688191f, -0.587785f},
	{0.442863f, 0.238856f, -0.864188f},
	{0.587785f, 0.425325f, -0.688191f},
	{0.688191f, 0.587785f, -0.425325f},
	{-0.147621f, 0.716567f, -0.681718f},
	{-0.309017f, 0.500000f, -0.809017f},
	{0.000000f, 0.525731f, -0.850651f},
	{-0.525731f, 0.000000f, -0.850651f},
	{-0.442863f, 0.238856f, -0.864188f},
	{-0.295242f, 0.000000f, -0.955423f},
	{-0.162460f, 0.262866f, -0.951056f},
	{0.000000f, 0.000000f, -1.000000f},
	{0.295242f, 0.000000f, -0.955423f},
	{0.162460f, 0.262866f, -0.951056f},
	{-0.442863f, -0.238856f, -0.864188f},
	{-0.309017f, -0.500000f, -0.809017f},
	{-0.162460f, -0.262866f, -0.951056f},
	{0.000000f, -0.850651f, -0.525731f},
	{-0.147621f, -0.716567f, -0.681718f},
	{0.147621f, -0.716567f, -0.681718f},
	{0.000000f, -0.525731f, -0.850651f},
	{0.309017f, -0.500000f, -0.809017f},
	{0.442863f, -0.238856f, -0.864188f},
	{0.162460f, -0.262866f, -0.951056f},
	{0.238856f, -0.864188f, -0.442863f},
	{0.500000f, -0.809017f, -0.309017f},
	{0.425325f, -0.688191f, -0.587785f},
	{0.716567f, -0.681718f, -0.147621f},
	{0.688191f, -0.587785f, -0.425325f},
	{0.587785f, -0.425325f, -0.688191f},
	{0.000000f, -0.955423f, -0.295242f},
	{0.000000f, -1.000000f, 0.000000f},
	{0.262866f, -0.951056f, -0.162460f},
	{0.000000f, -0.850651f, 0.525731f},
	{0.000000f, -0.955423f, 0.295242f},
	{0.238856f, -0.864188f, 0.442863f},
	{0.262866f, -0.951056f, 0.162460f},
	{0.500000f, -0.809017f, 0.309017f},
	{0.716567f, -0.681718f, 0.147621f},
	{0.525731f, -0.850651f, 0.000000f},
	{-0.238856f, -0.864188f, -0.442863f},
	{-0.500000f, -0.809017f, -0.309017f},
	{-0.262866f, -0.951056f, -0.162460f},
	{-0.850651f, -0.525731f, 0.000000f},
	{-0.716567f, -0.681718f, -0.147621f},
	{-0.716567f, -0.681718f, 0.147621f},
	{-0.525731f, -0.850651f, 0.000000f},
	{-0.500000f, -0.809017f, 0.309017f},
	{-0.238856f, -0.864188f, 0.442863f},
	{-0.262866f, -0.951056f, 0.162460f},
	{-0.864188f, -0.442863f, 0.238856f},
	{-0.809017f, -0.309017f, 0.500000f},
	{-0.688191f, -0.587785f, 0.425325f},
	{-0.681718f, -0.147621f, 0.716567f},
	{-0.442863f, -0.238856f, 0.864188f},
	{-0.587785f, -0.425325f, 0.688191f},
	{-0.309017f, -0.500000f, 0.809017f},
	{-0.147621f, -0.716567f, 0.681718f},
	{-0.425325f, -0.688191f, 0.587785f},
	{-0.162460f, -0.262866f, 0.951056f},
	{0.442863f, -0.238856f, 0.864188f},
	{0.162460f, -0.262866f, 0.951056f},
	{0.309017f, -0.500000f, 0.809017f},
	{0.147621f, -0.716567f, 0.681718f},
	{0.000000f, -0.525731f, 0.850651f},
	{0.425325f, -0.688191f, 0.587785f},
	{0.587785f, -0.425325f, 0.688191f},
	{0.688191f, -0.587785f, 0.425325f},
	{-0.955423f, 0.295242f, 0.000000f},
	{-0.951056f, 0.162460f, 0.262866f},
	{-1.000000f, 0.000000f, 0.000000f},
	{-0.850651f, 0.000000f, 0.525731f},
	{-0.955423f, -0.295242f, 0.000000f},
	{-0.951056f, -0.162460f, 0.262866f},
	{-0.864188f, 0.442863f, -0.238856f},
	{-0.951056f, 0.162460f, -0.262866f},
	{-0.809017f, 0.309017f, -0.500000f},
	{-0.864188f, -0.442863f, -0.238856f},
	{-0.951056f, -0.162460f, -0.262866f},
	{-0.809017f, -0.309017f, -0.500000f},
	{-0.681718f, 0.147621f, -0.716567f},
	{-0.681718f, -0.147621f, -0.716567f},
	{-0.850651f, 0.000000f, -0.525731f},
	{-0.688191f, 0.587785f, -0.425325f},
	{-0.587785f, 0.425325f, -0.688191f},
	{-0.425325f, 0.688191f, -0.587785f},
	{-0.425325f, -0.688191f, -0.587785f},
	{-0.587785f, -0.425325f, -0.688191f},
	{-0.688191f, -0.587785f, -0.425325f},
};

struct MD2AnimationType {
	int32_t begin;
	int32_t end;
	int32_t fps;
	std::string name;
};
const int32_t MD2_ANIMATION_TYPE_LIST_SIZE = 21;
static const MD2AnimationType MD2AnimationTypeList[MD2_ANIMATION_TYPE_LIST_SIZE] = {
	{  0,  39,  9, "STAND"}, // STAND
	{ 40,  45, 10, "RUN"}, // RUN
	{ 46,  53, 10, "ATTACK"}, // ATTACK
	{ 54,  57,  7, "PAIN_A"}, // PAIN_A
	{ 58,  61,  7, "PAIN_B"}, // PAIN_B
	{ 62,  65,  7, "PAIN_C"}, // PAIN_C
	{ 66,  71,  7, "JUMP"}, // JUMP
	{ 72,  83,  7, "FLIP"}, // FLIP
	{ 84,  94,  7, "SALUTE"}, // SALUTE
	{ 95, 111, 10, "FALLBACK"}, // FALLBACK
	{112, 122,  7, "WAVE"}, // WAVE
	{123, 134,  6, "POINT"}, // POINT
	{135, 153, 10, "CROUCH_STAND"}, // CROUCH_STAND
	{154, 159,  7, "CROUCH_WALK"}, // CROUCH_WALK
	{160, 168, 10, "CROUCH_ATTACK"}, // CROUCH_ATTACK
	{169, 172,  7, "CROUCH_PAIN"}, // CROUCH_PAIN
	{173, 177,  5, "CROUCH_DEATH"}, // CROUCH_DEATH
	{178, 183,  7, "DEATH_FALLBACK"}, // DEATH_FALLBACK
	{184, 189,  7, "DEATH_FALLFORWARD"}, // DEATH_FALLFORWARD
	{190, 197,  7, "DEATH_FALLBACKSLOW"}, // DEATH_FALLBACKSLOW
	{198, 198,  5, "BOOM"}, // BOOM
};

#include "pola/utils/spack.h"
struct MD2Header {
	int32_t magic;           // four character code "IDP2"
	int32_t version;         // must be 8
	int32_t skinWidth;	     // width of the texture
	int32_t skinHeight;      // height of the texture
	int32_t frameSize;       // size in bytes of an animation frame
	int32_t numSkins;        // number of textures
	int32_t numVertices;     // total number of vertices
	int32_t numTexcoords;    // number of vertices with texture coords
	int32_t numTriangles;    // number of triangles
	int32_t numGlCommands;   // number of opengl commands (triangle strip or triangle fan)
	int32_t numFrames;       // animation keyframe count
	int32_t offsetSkins;     // offset in bytes to 64 character skin names
	int32_t offsetTexcoords; // offset in bytes to texture coordinate list
	int32_t offsetTriangles; // offset in bytes to triangle list
	int32_t offsetFrames;    // offset in bytes to frame list
	int32_t offsetGlCommands;// offset in bytes to opengl commands
	int32_t offsetEnd;       // offset in bytes to end of file
} PACK_STRUCT;
struct MD2Vertex {
	uint8_t vertex[3];        // [0] = X, [1] = Z, [2] = Y
	uint8_t lightNormalIndex; // index in the normal table
} PACK_STRUCT;
struct MD2Frame {
	float	scale[3];           // first scale the vertex position
	float	translate[3];       // then translate the position
	char	name[16];           // the name of the animation that this key belongs to
	MD2Vertex vertices[1]; // vertex 1 of SMD2Header.numVertices
} PACK_STRUCT;
struct MD2Triangle {
	uint16_t vertexIndices[3];
	uint16_t textureIndices[3];
} PACK_STRUCT;
struct MD2TextureCoordinate {
	int16_t s;
	int16_t t;
} PACK_STRUCT;
#include "pola/utils/sunpack.h"

MD2MeshLoader::MD2MeshLoader() {
}

MD2MeshLoader::~MD2MeshLoader() {
}

bool MD2MeshLoader::available(io::InputStream* is) {
	MD2Header header;
	is->read(&header, sizeof(MD2Header));
	bool accept = true;
	if (header.magic != MD2_MAGIC_NUMBER || header.version != MD2_VERSION) {
		LOGE("MD2 Loader: Wrong file header\n");
		accept = false;
	}
	return accept;
}

pola::utils::sp<MeshLoader::Result> MD2MeshLoader::doLoadMesh(io::InputStream* is) {

#if !defined(USE_MD2_MESH)
	MD2Header header;
	is->read(&header, sizeof(MD2Header));

	if (header.magic != MD2_MAGIC_NUMBER || header.version != MD2_VERSION) {
		LOGE("MD2 Loader: Wrong file header\n");
		return nullptr;
	}

	// read Triangles
	is->seek(header.offsetTriangles);
	MD2Triangle *triangles = new MD2Triangle[header.numTriangles];
	if (!is->read(triangles, header.numTriangles *sizeof(MD2Triangle)))
	{
		delete[] triangles;

		LOGE("MD2 Loader: Error reading triangles.");
		return nullptr;
	}

	// read Vertices
	uint8_t buffer[MD2_MAX_VERTS*4+128];
	MD2Frame* frame = (MD2Frame*)buffer;
	is->seek(header.offsetFrames);

	Mesh* mesh = new Mesh;
	graphic::Geometry3D* geometry = (graphic::Geometry3D*) mesh->geometry();
	geometry->alloc(header.numTriangles * 3, FLAG_GEOMETRY_DEFAULT | FLAG_GEOMETRY_NORMAL | FLAG_GEOMETRY_UV);
	const int16_t count = header.numTriangles * 3;
	for (int16_t i = 0; i < count;  i += 3) {
		geometry->addIndex((uint16_t) i);
		geometry->addIndex((uint16_t) i + 1);
		geometry->addIndex((uint16_t) i + 2);
	}

	Animations* animations = new Animations;
	mesh->setAnimations(animations);

	is->seek(header.offsetFrames);

	graphic::Box3 boundingBox;
	int32_t frameIndex = 0;
	for (int32_t animationIndex = 0; animationIndex < MD2_ANIMATION_TYPE_LIST_SIZE; animationIndex ++) {
		if (frameIndex >= header.numFrames) {
			break;
		}
		MD2AnimationType animationType = MD2AnimationTypeList[animationIndex];
		FrameAnimation* animation = new FrameAnimation(animationType.name);
		animations->addAnimation(animation);
		float frameTime = 1.f / animationType.fps;
		for (frameIndex = animationType.begin; frameIndex <= animationType.end; frameIndex ++) {
			if (frameIndex >= header.numFrames) {
				break;
			}
			is->read(frame, header.frameSize);
			LOGD("FrameName=%s", frame->name);
			// add vertices
			FrameAnimation::KeyFrameData& frameData = animation->addKeyFrame(frameTime);
			frameData.positions.resize(header.numTriangles * 3);
			frameData.normals.resize(header.numTriangles * 3);
			graphic::vec3* positions = frameData.positions.data();
			graphic::vec3* normals = frameData.normals.data();
			for (int32_t j = 0; j < header.numTriangles; ++j) {
				for (int32_t ti = 0; ti < 3; ++ti) {
					uint32_t num = triangles[j].vertexIndices[ti];
					float x = frame->vertices[num].vertex[0];
					x = x * frame->scale[0] + frame->translate[0];
					float y = frame->vertices[num].vertex[1];
					y = y * frame->scale[1] + frame->translate[1];
					float z = frame->vertices[num].vertex[2];
					z = z * frame->scale[2] + frame->translate[2];
					positions[0] = {x, z, y};
					boundingBox.expandByPoint(positions[0]);
					positions ++;

					float nx = Q2_VERTEX_NORMAL_TABLE[frame->vertices[num].lightNormalIndex][0];
					float ny = Q2_VERTEX_NORMAL_TABLE[frame->vertices[num].lightNormalIndex][1];
					float nz = Q2_VERTEX_NORMAL_TABLE[frame->vertices[num].lightNormalIndex][2];
					normals[0] = {nx, nz, ny};
					normals ++;
				}
			}

			if (frameIndex == 0) {
				memcpy(geometry->positions(), frameData.positions.data(), sizeof(graphic::vec3) * header.numTriangles * 3);
				memcpy(geometry->normals(), frameData.normals.data(), sizeof(graphic::vec3) * header.numTriangles * 3);
			}
		}
	}
	geometry->setBoundingBox(boundingBox);

	is->seek(header.offsetTexcoords);
	MD2TextureCoordinate* textureCoords = new MD2TextureCoordinate[header.numTexcoords];
	is->read(textureCoords, sizeof(MD2TextureCoordinate)*header.numTexcoords);

	if (header.numFrames > 0) {
		float dmaxs = 1.0f / (header.skinWidth);
		float dmaxt = 1.0f / (header.skinHeight);
		graphic::vec2* uvs = geometry->uvs();;
		for (int32_t t = 0; t < header.numTriangles; ++t) {
			for (int32_t n = 0; n < 3; ++n) {
				int32_t index = t * 3 + n;
				uvs[index] = {(textureCoords[triangles[t].textureIndices[n]].s + 0.5f) * dmaxs, (textureCoords[triangles[t].textureIndices[n]].t + 0.5f) * dmaxt};
			}
		}
	}

	delete[] triangles;
	delete[] textureCoords;

	pola::utils::sp<MeshLoader::Result> result = new Result;
	result->mesh = mesh;
	return result;

#else
	MD2Header header;
	is->read(&header, sizeof(MD2Header));

	if (header.magic != MD2_MAGIC_NUMBER || header.version != MD2_VERSION) {
		LOGE("MD2 Loader: Wrong file header\n");
		return nullptr;
	}

	// read Triangles
	is->seek(header.offsetTriangles);
	MD2Triangle *triangles = new MD2Triangle[header.numTriangles];
	if (!is->read(triangles, header.numTriangles *sizeof(MD2Triangle)))
	{
		delete[] triangles;

		LOGE("MD2 Loader: Error reading triangles.");
		return nullptr;
	}

	// read Vertices
	uint8_t buffer[MD2_MAX_VERTS*4+128];
	MD2Frame* frame = (MD2Frame*)buffer;
	is->seek(header.offsetFrames);

	MD2AnimatedMesh* mesh = new MD2AnimatedMesh;
	graphic::Geometry3D* geometry = (graphic::Geometry3D*) mesh->geometry();
	geometry->alloc(header.numTriangles * 3, FLAG_GEOMETRY_DEFAULT | FLAG_GEOMETRY_NORMAL | FLAG_GEOMETRY_UV);
	const int16_t count = header.numTriangles * 3;
	for (int16_t i = 0; i < count;  i += 3) {
		geometry->addIndex((uint16_t) i);
		geometry->addIndex((uint16_t) i + 1);
		geometry->addIndex((uint16_t) i + 2);
	}

	mesh->frameTransforms.resize(header.numFrames);
	mesh->frameList.resize(header.numFrames);
	mesh->setFrameCount(header.numFrames);

	is->seek(header.offsetFrames);

	for (int32_t i = 0; i < header.numFrames; ++i) {

		is->read(frame, header.frameSize);

		LOGD("FrameName=%s", frame->name);

		// save keyframe scale and translation
		FrameTransform* frameTransforms = mesh->frameTransforms.data();
		frameTransforms[i].scale[0] = frame->scale[0];
		frameTransforms[i].scale[2] = frame->scale[1];
		frameTransforms[i].scale[1] = frame->scale[2];
		frameTransforms[i].translate[0] = frame->translate[0];
		frameTransforms[i].translate[2] = frame->translate[1];
		frameTransforms[i].translate[1] = frame->translate[2];

		graphic::Box3 boundingBox;

		mesh->frameList[i].resize(header.numTriangles * 3);
		FrameItem* frameItems = mesh->frameList[i].data();
		// add vertices
		for (int32_t j = 0; j < header.numTriangles; ++j) {
			for (int32_t ti = 0; ti < 3; ++ti) {
				FrameItem v;
				uint32_t num = triangles[j].vertexIndices[ti];
				v.pos[0] = frame->vertices[num].vertex[0];
				v.pos[2] = frame->vertices[num].vertex[1];
				v.pos[1] = frame->vertices[num].vertex[2];
				v.normal_index = frame->vertices[num].lightNormalIndex;

				*(frameItems++) = v;

				boundingBox.expandByPoint({v.pos[0] * frameTransforms[i].scale[0] + frameTransforms[i].translate[0],
					v.pos[1] * frameTransforms[i].scale[0] + frameTransforms[i].translate[0],
					v.pos[2] * frameTransforms[i].scale[0] + frameTransforms[i].translate[0]});
			}
		}
		geometry->setBoundingBox(boundingBox);
	}

	is->seek(header.offsetTexcoords);
	MD2TextureCoordinate* textureCoords = new MD2TextureCoordinate[header.numTexcoords];
	is->read(textureCoords, sizeof(MD2TextureCoordinate)*header.numTexcoords);

	if (header.numFrames > 0) {
		float dmaxs = 1.0f / (header.skinWidth);
		float dmaxt = 1.0f / (header.skinHeight);
		graphic::vec2* uvs = geometry->uvs();;
		for (int32_t t = 0; t < header.numTriangles; ++t) {
			for (int32_t n = 0; n < 3; ++n) {
				int32_t index = t * 3 + n;
				uvs[index] = {(textureCoords[triangles[t].textureIndices[n]].s + 0.5f) * dmaxs, (textureCoords[triangles[t].textureIndices[n]].t + 0.5f) * dmaxt};
			}
		}
	}

	delete[] triangles;
	delete[] textureCoords;
	pola::utils::sp<MeshLoader::Result> result = new Result;
	result->mesh = mesh;
	return result;
#endif
}

} /* namespace scene */
} /* namespace pola */
