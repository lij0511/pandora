/*
 * MD2MeshLoader.cpp
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#include <stdint.h>

#include "log/Log.h"
#include "scene/mesh/MD2MeshLoader.h"
#include "scene/mesh/MD2AnimatedMesh.h"

namespace pola {
namespace scene {

const int32_t MD2_MAGIC_NUMBER  = 844121161;
const int32_t MD2_VERSION       = 8;
const int32_t MD2_MAX_VERTS     = 2048;

struct MD2Header
{
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
};

struct MD2Vertex
{
	uint8_t vertex[3];        // [0] = X, [1] = Z, [2] = Y
	uint8_t lightNormalIndex; // index in the normal table
};

struct MD2Frame
{
	float	scale[3];           // first scale the vertex position
	float	translate[3];       // then translate the position
	char	name[16];           // the name of the animation that this key belongs to
	MD2Vertex vertices[1]; // vertex 1 of SMD2Header.numVertices
};

struct MD2Triangle
{
	uint16_t vertexIndices[3];
	uint16_t textureIndices[3];
};

MD2MeshLoader::MD2MeshLoader() {
}

MD2MeshLoader::~MD2MeshLoader() {
}

AnimatedMesh* MD2MeshLoader::doLoadMesh(io::InputStream* is) {

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
	MeshBuffer* meshBuffer = &mesh->meshBuffer;
	meshBuffer->alloc(header.numTriangles * 3);
	const int16_t count = header.numTriangles * 3;
	for (int16_t i = 0; i < count;  i+= 3) {
		meshBuffer->pushIndex((int16_t) i);
		meshBuffer->pushIndex((int16_t) i + 1);
		meshBuffer->pushIndex((int16_t) i + 2);
	}

	mesh->frameTransforms.resize(header.numFrames);
	mesh->frameList.resize(header.numFrames);
	mesh->frameCount = header.numFrames;

	is->seek(header.offsetFrames);

	for (int32_t i = 0; i < header.numFrames; ++i) {

		is->read(frame, header.frameSize);
		printf("sx=%f, sy=%f, sz=%f, num=%d\n", frame->scale[0], frame->scale[1], frame->scale[2], header.numFrames);
		printf("tx=%f, ty=%f, tz=%f\n", frame->translate[0] , frame->translate[1], frame->translate[2]);
		printf("name=%s\n", frame->name);

		// save keyframe scale and translation
		FrameTransform* frameTransforms = mesh->frameTransforms.editArray();
		frameTransforms[i].scale[0] = frame->scale[0];
		frameTransforms[i].scale[2] = frame->scale[1];
		frameTransforms[i].scale[1] = frame->scale[2];
		frameTransforms[i].translate[0] = frame->translate[0];
		frameTransforms[i].translate[2] = frame->translate[1];
		frameTransforms[i].translate[1] = frame->translate[2];

		mesh->frameList.editItemAt(i).resize(header.numTriangles * 3);
		FrameItem* frameItems = mesh->frameList.editItemAt(i).editArray();
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
			}
		}
	}
	delete[] triangles;

	return mesh;
}

} /* namespace scene */
} /* namespace pola */
