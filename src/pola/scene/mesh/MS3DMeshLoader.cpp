/*
 * MS3DMeshLoader.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "pola/scene/mesh/SkinnedMesh.h"
#include "pola/scene/mesh/MS3DMeshLoader.h"
#include "pola/log/Log.h"

namespace pola {
namespace scene {

#include "pola/utils/spack.h"
// File header
struct MS3DHeader {
	char id[10];
	int32_t version;
} PACK_STRUCT;
struct MS3DVertex {
	uint8_t flags;
	graphic::vec3 vertex;
	int8_t bone;
	uint8_t unused;
} PACK_STRUCT;
struct MS3DTriangle {
	uint16_t flags;
	uint16_t vertexIndices[3];
	graphic::vec3 vertexNormals[3];
	float uv[2][3];
	uint8_t smoothing;
	uint8_t group;
} PACK_STRUCT;
struct MS3DMaterial {
	char name[32];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emissive[4];
	float shininess;							//0.0 - 128.0
	float transparency;					//透明度 0.0 - 1.0
	char mode;
	char texture[128];					//贴图文件名
	char alphamap[128];				//透明贴图文件名
} PACK_STRUCT;
struct MS3DKeyFrame {
	float time;
	graphic::vec3 param;				//表示一个旋转或平移
} PACK_STRUCT;
struct MS3DJointInfo {
	uint8_t flags;
	char name[32];
	char parent[32];
	graphic::vec3 rotation;
	graphic::vec3 position;
	uint16_t numRotationFrames;
	uint16_t numTranslationFrames;
} PACK_STRUCT;
#include "pola/utils/sunpack.h"
struct MS3DGroup {
	uint8_t flags;
	char name[32];
	uint16_t numTriangles;
	uint16_t* triangleIndices;
	char materialIndex;
};



MS3DMeshLoader::MS3DMeshLoader() {
}

MS3DMeshLoader::~MS3DMeshLoader() {
}

bool MS3DMeshLoader::available(io::InputStream* is) {
	MS3DHeader header;
	is->read(&header, sizeof(MS3DHeader));

	if (strncmp(header.id, "MS3D000000", 10 ) != 0 ) {
		LOGE("MS3D Loader: Wrong file header\n");
		return false;
	}
	if (header.version < 3 || header.version > 4) {
		LOGE("Only Milkshape3D version 3 and 4 (1.3 to 1.8) is supported. Loading failed. version is %d\n", header.version);
		return false;
	}
	return true;
}

bool MS3DMeshLoader::doLoadMesh(io::InputStream* is, Mesh*& outMeshes, std::vector<MaterialDescription>& outMaterials) {
	MS3DHeader header;
	is->read(&header, sizeof(MS3DHeader));
	if (strncmp(header.id, "MS3D000000", 10 ) != 0 ) {
		LOGE("MS3D Loader: Wrong file header\n");
		return false;
	}
	if (header.version < 3 || header.version > 4) {
		LOGE("Only Milkshape3D version 3 and 4 (1.3 to 1.8) is supported. Loading failed. version is %d\n", header.version);
		return false;
	}

	SkinnedMesh* mesh = new SkinnedMesh;

	uint16_t numVertices = 0;
	is->read(&numVertices, sizeof(uint16_t));
	LOGD("numVertices=%u", numVertices);
	MS3DVertex* vertices = new MS3DVertex[numVertices];
	is->read(vertices, sizeof(MS3DVertex) * numVertices);

	uint16_t numTriangles = 0;
	is->read(&numTriangles, sizeof(uint16_t));
	LOGD("numTriangles=%u", numTriangles);
	MS3DTriangle* triangles = new MS3DTriangle[numTriangles];
	is->read(triangles, sizeof(MS3DTriangle) * numTriangles);

	uint16_t numGroups = 0;
	is->read(&numGroups, sizeof(uint16_t));
	LOGD("numGroups=%u", numGroups);
	MS3DGroup* groups = new MS3DGroup[numGroups];

	uint32_t totalNumTriangles = 0;
	for (unsigned i = 0; i < numGroups; i ++) {
		is->read(&groups[i].flags, sizeof(uint8_t));
		is->read(groups[i].name, sizeof(groups[i].name));
		is->read(&groups[i].numTriangles, sizeof(uint16_t));
		uint16_t* triangleIndices = new uint16_t[groups[i].numTriangles];
		groups[i].triangleIndices = triangleIndices;
		is->read(triangleIndices, sizeof(uint16_t) * groups[i].numTriangles);
		is->read(&groups[i].materialIndex, sizeof(char));
		LOGW("groupName=%s, materialIndex=%d, numTriangles=%u", groups[i].name, groups[i].materialIndex, groups[i].numTriangles);
		totalNumTriangles += groups[i].numTriangles;
	}

	graphic::Geometry3D* geometry = (graphic::Geometry3D*) mesh->localGeometry();
	graphic::Geometry3D* geometryM = (graphic::Geometry3D*) mesh->geometry();
	geometry->alloc(totalNumTriangles * 3, FLAG_GEOMETRY_DEFAULT | FLAG_GEOMETRY_NORMAL | FLAG_GEOMETRY_UV);
	geometryM->alloc(totalNumTriangles * 3, FLAG_GEOMETRY_DEFAULT | FLAG_GEOMETRY_NORMAL | FLAG_GEOMETRY_UV);
	uint32_t counter = 0;
	for (unsigned i = 0; i < numGroups; i ++) {
		if (numGroups > 1) {
			mesh->addGroup(counter, groups[i].numTriangles * 3, groups[i].materialIndex < 0 ? 0 : groups[i].materialIndex);
		}
		uint16_t* triangleIndices = groups[i].triangleIndices;
		graphic::vec3* positions = geometry->positions() + counter;
		graphic::vec3* normals = geometry->normals() + counter;
		graphic::vec2* uvs = geometry->uvs() + counter;
		for (uint16_t j = 0; j < groups[i].numTriangles; j ++) {
			*(positions ++) = vertices[triangles[triangleIndices[j]].vertexIndices[0]].vertex;
			*(positions ++) = vertices[triangles[triangleIndices[j]].vertexIndices[1]].vertex;
			*(positions ++) = vertices[triangles[triangleIndices[j]].vertexIndices[2]].vertex;
			*(normals ++) = triangles[triangleIndices[j]].vertexNormals[0];
			*(normals ++) = triangles[triangleIndices[j]].vertexNormals[1];
			*(normals ++) = triangles[triangleIndices[j]].vertexNormals[2];

			*(uvs ++) = {triangles[triangleIndices[j]].uv[0][0], triangles[triangleIndices[j]].uv[1][0]};
			*(uvs ++) = {triangles[triangleIndices[j]].uv[0][1], triangles[triangleIndices[j]].uv[1][1]};
			*(uvs ++) = {triangles[triangleIndices[j]].uv[0][2], triangles[triangleIndices[j]].uv[1][2]};
		}
		counter += groups[i].numTriangles * 3;
		delete triangleIndices;
	}
	memcpy(geometryM->uvs(), geometry->uvs(), geometry->uvCount() * sizeof(graphic::vec2));
	// TODO Skinning.
	memcpy(geometryM->positions(), geometry->positions(), geometry->positionCount() * sizeof(graphic::vec3));
	memcpy(geometryM->normals(), geometry->normals(), geometry->normalCount() * sizeof(graphic::vec3));

	uint16_t numMaterials = 0;
	is->read(&numMaterials, sizeof(uint16_t));
	LOGW("numMaterials=%u", numMaterials);
	if (numMaterials > 0) {
		outMaterials.clear();
		MS3DMaterial* materials = new MS3DMaterial[numMaterials];
		is->read(materials, sizeof(MS3DMaterial) * numMaterials);
		for (unsigned i = 0; i < numMaterials; i ++) {
			MaterialDescription material;
			material.ambient = {materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2], materials[i].ambient[3]};
			material.diffuse = {materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2], materials[i].diffuse[3]};
			material.specular = {materials[i].specular[0], materials[i].specular[1], materials[i].specular[2], materials[i].specular[3]};
			material.emissive = {materials[i].emissive[0], materials[i].emissive[1], materials[i].emissive[2], materials[i].emissive[3]};
			material.shininess = materials[i].shininess;
			material.texture = materials[i].texture;
			outMaterials.push_back(material);
			LOGD("materialName=%s, texture=%s", materials[i].name, materials[i].texture);
		}
	}

	float fps = 2.f;
	is->read(&fps, sizeof(float));
	LOGD("fps=%f", fps);
	is->skip(4 + 4);

	uint16_t numJoints = 0;
	is->read(&numJoints, sizeof(uint16_t));
	LOGD("numJoints=%u", numJoints);
	if (numJoints > 0) {
		MS3DJointInfo jointInfo;
		std::vector<MS3DKeyFrame> keyFrames;
		for (unsigned i = 0; i < numJoints; i ++) {
			is->read(&jointInfo, sizeof(MS3DJointInfo));
			keyFrames.resize(jointInfo.numRotationFrames);
			is->read(keyFrames.data(), sizeof(MS3DKeyFrame) * jointInfo.numRotationFrames);

			keyFrames.resize(jointInfo.numTranslationFrames);
			is->read(keyFrames.data(), sizeof(MS3DKeyFrame) * jointInfo.numTranslationFrames);
			LOGD("joint=%s, numRotationFrames=%u, numTranslationFrames=%u", jointInfo.name, jointInfo.numRotationFrames, jointInfo.numTranslationFrames);
		}
	}

	delete[] vertices;
	delete[] triangles;
	delete[] groups;

	geometry->computeBoundingBox();
	outMeshes = mesh;
	return true;
}

} /* namespace scene */
} /* namespace pola */
